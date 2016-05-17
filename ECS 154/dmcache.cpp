//dmcache.cpp
//Author: Ian Rosner
//Date: 11/25/2015
//Class: ECS 154A
#include <iostream>
#include <fstream> //file i/o
#include <string>  //getline
#include <sstream> //hex conversion
#include <map> //RAM implementation

using namespace std;

static const string INPUT_FILENAME = "dmtest-input2.txt"; //read first cmd line arg
static const string OUTPUT_FILENAME = "dm-out.txt";


// 16 bits in address
// cache capacity = 512, block size = 8
// 512/8 = 64 lines/rows in direct cache at 8 bytes each
// 64 = 2^6, 6 bits for index
// 8  = 2^3, 3 bits for offset
// 16 - 9  = 7 bits for tag
// tttt ttti iiii iooo

//other misc info:

/*
Bytes	Function
1-2		16 bit address
3		Read/Write (read = all 0; write = all 1)
4		8 bits of data	*/

//byte-addressable, but blocks are always read/written in multiples of 8
// when fetching a line, cases:
/*	1. first encounter
set cacheline tag to tag
write data, contents should otherwise be 0
ram is empty for this index

2. cache has entry
a) tag matches
modify data as per usual

b) tag collides
send current into ram
look up this tag in ram

i) tag is in ram
load this ram into cache, set dirty bit to true (?)

ii) tag isnt in ram
reset line after current sent to ram
then write data	   */

int hexToInt(string input){
	stringstream ss;
	int converted;

	ss << input;
	ss >> hex >> converted;
	return converted; //input string sent through std::hex stream
}

int getTag(string address){
	//first character, left 3 bits of 2nd character
	int tag = hexToInt(address.substr(0, 2));
	//trim off 8th bit
	tag >> 1;

	return tag;
}

int getIndex(string address){
	//2nd char -> 1st bit, 3rd char -> all, 4th char -> 4th bit

	int msb = hexToInt(address.substr(1, 1)); //2nd char
	int mid = hexToInt(address.substr(2, 1)); //3rd char
	int lsb = hexToInt(address.substr(3, 1)); //4th char

	msb = msb & 0x1; //get 1st bit
	lsb = lsb >> 3;  //get 4th bit

	mid = mid << 1; //shift right (make room for lsb)

	if(lsb == 1) mid = mid + 1; //add 1 if our first bit is set
	if(msb == 1) mid = mid + 32;

	return mid;
}

int getOffset(string address){
	int offset = hexToInt(address.substr(3, 1)); //pass it the first character

	//however, this character is 4 bits, and offset is only 3 bits -- maximum value of 7
	//so if int value is over 7, make sure we remove the 4th bit
	offset = offset & 0x7;

	return offset;
}

class CacheLine {
private:
	int tag; //identifier
	bool dirtybit;

	string block[8]; //each line contains 8 bytes

public:
	bool exists; //public to easily set & get

	CacheLine(){ //default constructor
		tag = -1;
		dirtybit = 0;
		exists = false;

		for(int i = 0; i < 8; i++){
			block[i] = "00"; //initialize to 00
		}
	}

	CacheLine &operator=(const CacheLine &rhs){ //assignment operator
		this->tag = rhs.tag;
		this->dirtybit = rhs.dirtybit;
		this->exists = rhs.exists;

		for(int i = 0; i < 8; i++){
			this->block[i] = rhs.block[i];
		}

		return *this;
	}

	bool getDirty(){
		return dirtybit;
	}

	string getByte(int offset){
		if(offset > 7 || offset < 0){
			cerr << "offset out of bounds!" << endl;
			throw "Invalid offset when trying to read byte!";
		}
		else {
			return block[offset];
		}
	}

	int getTag(){
		return tag;
	}

	void setTag(int input){ //this func should only be called once
		tag = input;
	}

	void setByte(int offset, string data){
		if(offset >= 8){
			cerr << "offset out of bounds!" << endl;
		}
		else {
			block[offset] = data;
		}
	}

	void setDirty(bool bit){
		dirtybit = bit;
	}

	void reset(int new_tag){ //to be called after saving and fresh tag
		dirtybit = 0;
		tag = new_tag;
		exists = true;

		for(int i = 0; i < 8; i++){
			block[i] = "00";
		}
	}
};

class RAM {
private:
	//2^16 chars
	//slot for each possible 16-bit value ?
	//each possible tag, index, offset

	//cachelines indexed by tag

	map <int, CacheLine> memory;

	int makeKeyvalue(int tag, int index){
		int keyvalue = tag; //return value

		keyvalue = keyvalue << 6; //make room for index
		keyvalue = keyvalue + index;		

		return keyvalue;
	}


public:
	const CacheLine &getLine(int tag, int index){ //lookup tag of line
		return memory.at(makeKeyvalue(tag, index));
	}

	bool existsInRAM(int tag, int index){
		int keyvalue = makeKeyvalue(tag, index);

		if(memory.count(keyvalue) != 0){ //if we have an entry at this keyvalue,
			return true;				 //we may proceed
		}
		else {
			return false;
		}
	}

	void set(CacheLine inputLine, int index){
		int tag = inputLine.getTag();

		//memory.insert_or_assign(makeKeyvalue(tag, index), inputLine); //c++17 only apparently
		memory[makeKeyvalue(tag, index)] = inputLine; //hopefully side-effect free
	}
};

class Cache {
private:
	//Address contents[64]
	CacheLine lines[64]; //each entry contains 2 characters (4 bits/char -> 2 chars -> 8 bits -> 1 byte)
	RAM ram;

	void writeBack(int index){
		if(lines[index].getDirty() == 1){ //write-back policy - only write if dirty is set
			lines[index].setDirty(false); //clear dirty
			ram.set(lines[index], index);
		}
	}

	bool evict(int tag, int index){ //checks to see if line should be evicted
		if(lines[index].getTag() != tag){
			//tags dont match, we need to replace
			return true;
		}
		else {
			return false;
		}
	}
	void fetch(int tag, int index){
		//this function sets up the cache line within the cache
		//loads cache line from ram if necessary

		/* in which a write miss causes the appropriate line to be brought
		into the cache from memory, and the write's value to update the
		correct part of the line in the cache, which will then become dirty. */
		if(lines[index].exists == false){ //check if this is a cold cache
			lines[index].exists = true;
			lines[index].setTag(tag);
		}
		else if(evict(tag, index)){ // there is a cache miss & we need to swap between ram
			writeBack(index); //save current cache todo - determine what vars this needs

							  //after saving, does our new tag exist in ram?
			if(ram.existsInRAM(tag, index) == true){ //if it does,
				lines[index] = ram.getLine(tag, index); //load ram into cache

														//set our dirty bit to reflect that data has been modified
				lines[index].setDirty(true);
			}
			else { //tag doesnt exist in ram, so just reset current line index
				lines[index].reset(tag); //re-initialized to 00 for byte data
			}
		}
	}


public:
	void writeLine(string address, string data){
		int tag = getTag(address); //tag = first 2 hex values (8 bits)
		int index = getIndex(address); //5 bits, do conversion todo

		fetch(tag, index); //grab line from ram (if necessary)

						   //after correct line ensured in cache, set data & set dirtybit
		lines[index].setByte(getOffset(address), data);
		lines[index].setDirty(true); //potentially have more conditions for this ?
	}

	void read(string address, ofstream &outfile){
		//format is described in hw5.pdf
		/* addr -8-bytes-of-data- hit/miss dirtybit */
		int tag = getTag(address); //tag = first 2 hex values (8 bits)
		int index = getIndex(address); //5 bits, do conversion todo
		int offset = getOffset(address);

		bool hit = 0;
		bool dirty = lines[index].getDirty(); //Note that the dirty bit will displayed as 1 if the original dirty bit was set, even if there is a read miss that will cause the dirty bit to be cleared

		if(tag == lines[index].getTag()){
			//hit!
			hit = 1;
		}
		else {
			fetch(tag, index); //miss, but 2 potential different types

			//loaded from memory but not writing - clear dirty bit
			lines[index].setDirty(false);
		}

		//now do our output
		CacheLine outLine = lines[index];
		outfile << address << " "; //start with address and a space

		for(int i = 7; i >= 0; i--){ //read each byte in the block
			outfile << outLine.getByte(i); //modified - do it backwards because of reasons
		}
		//wrap up output
		outfile << " " << hit << " " << dirty << endl; // hit/miss, dirty bit, new line
	}
};



void parseInput(string line, Cache &cache, ofstream &fileout){
	if(line.size() != 10){
		cerr << "Input line is not desired size!" << endl;
		return;
	}

	string addr = line.substr(0, 4); //first 4 chars
	string op = line.substr(5, 2); //get middle 2 letters

	if(op == "FF"){ //write operation
		cache.writeLine(addr, line.substr(8, 2)); //address & last 2 chars (data)
	}
	else if(op == "00"){ //read operation
						 //check tag on address
						 //if wrong tag, load from ram
						 //write output to file
		cache.read(addr, fileout);
	}
	else {
		cerr << "Unknown op " << op << " in input file." << endl; //on the off chance
	}
}

int main(int argc, char** argv){
	Cache cache; //create our cache

	ifstream inputFile; //open up the input file
	
	inputFile.open(argv[1]);

	ofstream fileout; //create a file stream for outputting read cmds
	fileout.open(OUTPUT_FILENAME.c_str());

	for(string line; getline(inputFile, line); ){ //for every line in the input file,
		parseInput(line, cache, fileout);		  //parse the read/write instruction
	}

	//std::cout << "Output file " << OUTPUT_FILENAME << " created." << std::endl; //done!
																				//cin.get(); //pause
	return 0;
}