#include <iostream>
#include <iomanip> //time func
#include "statistics.h"
using namespace std;

/* programmed by ian rosner
for douglass' cisp440 spring 2015
Craps		
Stats needed	
10,000 games	
overall win loss pctg
pctg win on first throw
pctg lose on first throw
pctg get a point	
pctg for point of 4, 5, 6, 8, 9, 10
point of 4 - 10 pctg win lose
all other points	
win lose pctg with a point
pctg of time roll of dice 2-12
longest run with a point
Due 3/4 */

int rollTheDice();

int main(){
	srand(time(NULL)); //set new seed for random generator
	// ...
	bool gameEnd = false; //track game state for while loop
	int point = 0, pointStreak = 0; //what our point is & streak
	int d1, d2, roll; //dice

	Statistics stats;

	for(int i = 0; i < 10000; i++){
		//reset our vars
		point = 0;
		pointStreak = 0;
		gameEnd = false;

		while(gameEnd != true){
			//do game stuff
			d1 = rollTheDice();
			d2 = rollTheDice();

			roll = d1 + d2;

			if(point == 0){ //if first roll
				stats.inputFirstThrow(d1, d2); //collect stats

				switch(roll){
				case 2:
				case 3:
				case 7:
				case 11:
				case 12:
					//win & lose condition --
					gameEnd = true; //game is over
					break;
				default: //point case
					point = roll;
					pointStreak = 1;
					break;
				}
			} else if(point > 0){
				//this is a subsequent roll
				stats.inputThrow(d1, d2, point);
				if(roll == point){
					//win!
					gameEnd = true;
					stats.inputPtStrk(pointStreak);
				} else if(roll == 7){
					//we lose
					gameEnd = true;
				} else {
					pointStreak++;
					//cout << "point streak of " << pointStreak << endl;
					//continue rolling
				}
			} //end roll check
		} //game end or re-roll
	} //end 10k games

	//print statistics out
	stats.printReport();
	system("pause");
}

int rollTheDice(){
	return (rand() % 6) + 1;
}