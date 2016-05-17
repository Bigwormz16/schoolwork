//sacache.cpp
//Author: Ian Rosner
//Date: 11/25/2015
//Class: ECS 154A
#include <iostream>
#include <fstream> //file i/o
#include <string>  //getline
#include <sstream> //hex conversion
#include <map> //RAM implementation
#include <list> //lru

using namespace std;

static const string INPUT_FILENAME = "satest-1000-1.txt"; //read first cmd line arg
static const string OUTPUT_FILENAME = "sa-out.txt";

// 4-way set associative
// 16 bits in address
// cache capacity = 512, block size = 8
// 4 ways per set
// 512/(8*4) = 512/32 = 16 lines of 4 sets each

// offset = 2^3 = 3 bits
// index = 2^4  = 4 bits
// tag = 16-7   = 9 bits

// chr1 chr2 chr3 chr4
// tttt tttt tiii iooo

/* cache contains 16 sets
	each set contains 4 ways
	each way contains 1 data block*/

int hexToInt(string input){
	stringstream ss;
	int converted;

	ss << input;
	ss >> hex >> converted;
	return converted; //input string sent through std::hex stream
}

int getTag(string address){
	//first 2 characters + leftmost bit of 3rd
	int tag = hexToInt(address.substr(0, 2)); //grab first 2 chars
	int lsb = hexToInt(address.substr(2, 1)); //grab 3rd char
	lsb = lsb >> 3; //trim first 3

	tag = tag << 1; //add 9th bit
	tag = tag + lsb;

	return tag;
}

int getIndex(string address){
	//rightmost 3 bits of 3rd char
	//leftmost bit of 4th char

	int msb = hexToInt(address.substr(2, 1)); //3rd char

	int lsb = hexToInt(address.substr(3, 1)); //4th char
	lsb = lsb >> 3; //trim first 3 bits

	msb = msb & 0x7; //mask leftmost bit -- & 0111
	msb = msb << 1; //add room for 1s bit
	msb = msb + lsb; //add our lsb

	return msb;
}

int getOffset(string address){
	int offset = hexToInt(address.substr(3, 1)); //pass it the first character
	offset = offset & 0x7; //mask first bit -> 0b0111

	return offset;
}

class CacheLine {
private:
	int tag; //identifier
	bool dirtybit;

	string block[8]; //each line contains 8 bytes

public:
	//bool exists; //public to easily set & get
	bool previousdirty;

	CacheLine(){ //default constructor
		tag = -1;
		dirtybit = 0;
		previousdirty = 0;
		//exists = false;

		for(int i = 0; i < 8; i++){
			block[i] = "00"; //initialize to 00
		}
	}

	CacheLine &operator=(const CacheLine &rhs){ //assignment operator
		this->tag = rhs.tag;
		this->previousdirty = this->dirtybit;
		this->dirtybit = rhs.dirtybit;
		//this->exists = rhs.exists;

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
		//exists = true;

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

		keyvalue = keyvalue << 4; //make room for index
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

class CacheSlot {
private:
	static const int ways = 4; //4-way set associate
	CacheLine blocks[ways];

	int used;
	list<int> recency; //contains most recent index used (front) to least recent index used (back)


	int get_lru(){
		int r = recency.back(); //get last element in list
		recency.pop_back();		//remove back,
		recency.push_front(r);  //push to front

		return r;
	}

	void update_lru(int index){
		//sometimes lru needs to be updated
		//if something is *NOT* evicted but *IS* used
		recency.remove(index);
		recency.push_front(index); //most recently used item now in front of list
	}
	
public:
	//public methods
	CacheSlot(){
		used = 0;
		//for(int i = 0; i < 4; i++){
		//	recency.push_front(i); //initialize LRU list -- 0 1 2 3
		//}

	}	

	pair<bool, int> fetch(string address, RAM &ram){
		//1. check if tag is in cache
		//2. check if each way has been initialized
		//3. check ram for tag
		//4. else, reset a block
		int tag = getTag(address);
		int index = getIndex(address);

		int slot; //which column in the 4-way set

		pair<bool, int> lookupResult = lookup(tag);

		if(lookupResult.first == true){ //hit
			//tag already exists in cache
			slot = lookupResult.second;
			update_lru(slot);
		} else if(used < 4){
			//use next empty slot
			slot = used;
			blocks[slot].reset(getTag(address));

			update_lru(slot);
			used++;
			//not dirty
		} else { //miss & replace
			slot = get_lru(); //LRU updated here for all miss cases

			bool tempDirty = blocks[slot].getDirty();

			//write back
			if(blocks[slot].getDirty()){
				blocks[slot].setDirty(false); //clear dirty
				ram.set(blocks[slot], index); //save to RAM
			}

			if(ram.existsInRAM(tag, index)){
				//load from ram
				blocks[slot] = ram.getLine(tag, index);
			} else {
				//item doesnt exist in cache OR ram
				blocks[slot].reset(tag);
				//blocks[slot].setDirty(true);
			}
			blocks[slot].previousdirty = tempDirty;
		}
		return make_pair(lookupResult.first, slot); //hit or miss & slot to read/write
	}

	void setData(string address, string data, RAM &ram){
		int slot = fetch(address, ram).second;
		
		blocks[slot].setByte(getOffset(address), data);
		blocks[slot].setDirty(true);
	}

	string getData(string address, RAM &ram){
		int tag = getTag(address);
		int index = getIndex(address);
		int offset = getOffset(address);

		stringstream data;
		data << address << " ";

		bool hit;
		bool dirty;

		int way;

		pair<bool, int> fetchResult = fetch(address, ram);
		way = fetchResult.second;

		if(fetchResult.first == true){
			//hit
			hit = 1;
			dirty = blocks[way].getDirty();
		}
		else {
			//miss
			hit = 0;
			dirty = blocks[way].previousdirty;
		}


		//if((lookup(tag).first == false) && used < 4){ //if first 4 havent been init
		//	way = used;
		//	update_lru(way);
		//	blocks[way].reset(tag);
		//	used++;

		//	hit = false;
		//	dirty = 0;
		//} else {
		//	pair<bool, int> fetchResult = fetch(address, ram);
		//	hit = fetchResult.first;
		//	way = fetchResult.second;
		//	dirty = blocks[way].getDirty();

		//	if(hit == false){
		//		//item isnt in cache
		//		dirty = blocks[way].previousdirty;
		//	}
		//}


		//dirty bit setting
		//if we missed and had to replace, use previous thing

		for(int i = 7; i >= 0; i--){
			data << blocks[way].getByte(i);
		}
		
		data << " " << hit << " " << dirty; // << blocks[way].previousdirty;


		return data.str();
	}

	pair<bool, int> lookup(int tag){
		//first : bool - true if item exists in set
		//second : int - index if item exists in set, 0 otherwise
		for(int i = 0; i < ways; i++){
			if(blocks[i].getTag() == tag){
				//found tag in set
				return make_pair(true, i);
			}
		}
		return make_pair(false, 0);
	}
};

class Cache {
private:
	CacheSlot lines[16]; //each entry contains 2 characters (4 bits/char -> 2 chars -> 8 bits -> 1 byte)
	RAM ram;

public:

	void writeLine(string address, string data){
		//see CacheSlot.setData( ) for details
		lines[getIndex(address)].setData(address, data, ram);
	}

	void read(string address, ofstream &outfile){
		int index = getIndex(address);

		outfile << lines[index].getData(address, ram) << endl;
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
	if(argc > 1){
		inputFile.open(argv[1]);
	} else {
		inputFile.open(INPUT_FILENAME.c_str());
	}

	ofstream fileout; //create a file stream for outputting read cmds
	fileout.open(OUTPUT_FILENAME.c_str());

	for(string line; getline(inputFile, line); ){ //for every line in the input file,
		parseInput(line, cache, fileout);		  //parse the read/write instruction
	}

	//std::cout << "Output file " << OUTPUT_FILENAME << " created." << std::endl; //done!
	//cin.get(); //pause
	return 0;
}