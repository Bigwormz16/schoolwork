/*				
next problem	
3 cards		
1 card w/w	
b/w		
b/b		
Strategies	1. opposite color	
2. same color	
3. always guess white
4.always guess black
5. alternate w        and b

6. random pick	
Due 3/11   30 points for program   10 points for explanation */

#include <iostream>
#include <time.h> //for random seed
#include <iomanip>
using namespace std;

enum COLOR { BLACK, WHITE }; //card color possibilities

class Statistics {
public:
	Statistics();
	void testMethods(COLOR input, COLOR answer);
	void print();
private:
	bool alternator;
	int wins[6]; //wins for each method
	int games;
	inline COLOR opposite(COLOR input){ //wins[0]
		return COLOR(!input);
	}
	inline COLOR same(COLOR input){
		return input;
	}
	inline COLOR guessWhite(){
		return WHITE;
	}
	inline COLOR guessBlack(){
		return BLACK;
	}
	COLOR alternate(){ //uses bool alternator
		alternator = !alternator;
		return COLOR(!alternator);
	}
	COLOR random(){ //wins[6]
		return COLOR(rand() % 2);
	}
};

int main(){
	srand(time(0)); //set rand seed

	COLOR cards[3][2] = {
		{BLACK, BLACK}, //cards[0] = double black
		{BLACK, WHITE}, //cards[1] = black, white
		{WHITE, WHITE}  //cards[2] = double white
	};

	Statistics stats;

	short draw = 0, //card 1 - 3 ?
		  side = 0; //side 1 or 2?

	for(int i = 0; i < 10000; i++){
		draw = rand() % 3;
		side = rand() % 2;
		stats.testMethods(cards[draw][side], cards[draw][!side]); //pass in shown side and flip side
		//method does everything else
	}

	stats.print();

	system("pause");
}

Statistics::Statistics(){ //constructor
	for(int i = 0; i < 6; i++){
		wins[i] = 0; //initialize array
	}
	alternator = 0;
	games = 0;
}

void Statistics::testMethods(COLOR input, COLOR answer){
	/* 1. opposite
	   2. same
	   3. white
	   4. black
	   5. alternating
	   6. random */
  //if(method(input) == correct ans) increment win count
	if(opposite(input) == answer) wins[0]++;
	if(same(input) == answer) wins[1]++;
	if(guessWhite() == answer) wins[2]++;
	if(guessBlack() == answer) wins[3]++;
	if(alternate() == answer) wins[4]++;
	if(random() == answer) wins[5]++;

	games++;
}

void Statistics::print(){
	cout << " --- STATISTICS --- GAMES PLAYED:  " << games << endl << endl;
	cout << setw(29) << left << "METHOD USED" << right << "WIN PERCENT" << endl;
	cout << setw(40) << setfill('=') << "" << setfill(' ') << endl; //draw line, set decimal precision

	cout << setw(29) << left << "1. Opposite Color"		<< setw(10) << right << double(wins[0])/games*100 << "%" << endl;
	cout << setw(29) << left << "2. Same Color" << setw(10) << right << double(wins[1])/games*100 << "%" << endl;
	cout << setw(29) << left << "3. Always White"	<< setw(10) << right << double(wins[2])/games*100 << "%" << endl;
	cout << setw(29) << left << "4. Always Black"	<< setw(10) << right << double(wins[3])/games*100 << "%" << endl;
	cout << setw(29) << left << "5. Alternate W/B"	<< setw(10) << right << double(wins[4])/games*100 << "%" << endl;
	cout << setw(29) << left << "6. Random Pick"	<< setw(10) << right << double(wins[5])/games*100 << "%" << endl;
	
	cout << endl;
}