/*
16 line page table
4KB pages
physical address space 1GB
virtual  address space 4GB

Your simulator will read a file that contains virtual addresses that are needed. The first 16
lines in the file are the addresses of the first bytes of each page in the page table. The rest of the lines are addresses that
are currently needed by the executable. Note that the addresses are not necessarily that of the first byte of a page. After
the initial 16, for each address read, your program will write to a file named vm-out.txt a line that lists the virtual
addresses (in hex) of the first bytes of the four pages currently in RAM. The list should always start from the first entry in
the four-page entry table. Your output file will be diffed with mine. If diff prints any differences, then you will receive a
zero. My executable, test files, and a program to create test files are in ~ssdavis/154/p5.

You will find Stallings’ virtual memory appendix available on the course website under homework assignments.
*/

/*
 *
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>

#include <list> // for LRU
using namespace std;

static const string OUTPUT_FILENAME = "vm-out.txt";


class PageTable {
public:
	string line[16];
	bool ref[16];
	int pos;

public:
	PageTable(){
		pos = 0;
		for(int i = 0; i < 16; i++){
			ref[i] = false;
		}
	}

	void setLine(string input, int linenum){
		line[linenum] = input;
	}

	string getLine(string searchstr){
		for(int i = 0; i < 16; i++){
			if(line[i].substr(0, 4) == searchstr.substr(0, 4)){
				return line[i];
			}
		}
	}

} PageTable;

class FrameHolder {
	static const int count = 4;
	string frames[4];
	bool ref[4];

	int used;

public:
	FrameHolder(){
		used = 0;

		for(int i = 0; i < count; i++){
			ref[i] = 0;
		}
	}

	void lookup(string inFrame){
		for(int i = 0; i < count; i++){
			if(frames[i].substr(0, 4) == inFrame){
				//hoorah.
				ref[i] = 1;
				return;
			}
		}

		if(used < 4){
			frames[used] = PageTable.getLine(inFrame);
			used++;
			return;
		}

		//otherwise...
		//do clock algo
		int iter = PageTable.pos;
		bool replaced = false;
		while(replaced == false){
			//check ref bits
			if(ref[iter] == 0){
				//found spot to replace!
				frames[iter] = PageTable.getLine(inFrame);
				replaced = true;
				ref[iter] = 1; //frame is marked as in-use.
			} else {
				ref[iter] = 0;
				iter++;
				iter = iter % count;
			}
		}//end while
		PageTable.pos = iter; //save clock hand pos

	}//end func

	void printFrames(ofstream &fileout){
		cout << frames[0];
		fileout << frames[0];

		for(int i = 1; i < used; i++){
			cout << " " << frames[i];
			fileout << " " << frames[i];
		}
		cout << endl;
		fileout << endl;
	}

} Holder;



void parseInput(string line, ofstream &fileout){
	string wantedFrame = line.substr(0, 4); //get first 5 chars
	Holder.lookup(wantedFrame);
	Holder.printFrames(fileout);
}

void initialize(string line, int counter){
	PageTable.setLine(line, counter);
}

int main(int argc, char** argv){
	ifstream inputFile; //open up the input file
	//inputFile.open(argv[1]);
	inputFile.open("vmtest.txt");

	ofstream fileout; //create a file stream for outputting read cmds
	fileout.open(OUTPUT_FILENAME.c_str());

	int loopct = 0;
	for(string line; getline(inputFile, line); ){ //for every line in the input file,
		if(loopct < 16){
			initialize(line, loopct);
			loopct++;
		}
		else {
			parseInput(line, fileout);		  //parse the read/write instruction
		}
	}

	//std::cout << "Output file " << OUTPUT_FILENAME << " created." << std::endl; //done!
	cin.get(); //pause
	return 0;
}