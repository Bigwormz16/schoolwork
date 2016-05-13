#include "statistics.h"
#include <iostream>
#include <iomanip>
/* function definitions for craps statistics collector */

Statistics::Statistics(){
	totalWin = 0;
	totalLoss = 0;
	totalThrow = 0;
	totalGame = 0;
	firstThrowLoss = 0;
	firstThrowWin = 0;
	pointTotal = 0;
	pointWin = 0;
	pointLose = 0;
	longestPointRun = 0;
	//pointOther = 0;
	
	//initialize arrays
	for(int i = 0; i < 6; i++){
		pointCount[i] = 0;
		pointWinLose[i] = 0;
	}
	for(int i = 0; i < 11; i++){ //0 - 10 diceRoll for rolls of 2 through 12
		diceRoll[i] = 0;
	}
}

void Statistics::inputFirstThrow(int dice1, int dice2){
	//case of win/lose/point
	int roll = dice1 + dice2;

	totalThrow++;
	totalGame++;
	diceRoll[roll - 2]++; //index [0] -> dice roll of 2

	switch(roll){
	case 7:
	case 11:
		firstThrowWin++;
		totalWin++;
		break;
	case 2:
	case 3:
	case 12:
		firstThrowLoss++;
		totalLoss++;
		break;
	case 4:
		pointCount[0]++;
		pointTotal++;
		break;
	case 5:
		pointCount[1]++;
		pointTotal++;
		break;
	case 6:
		pointCount[2]++;
		pointTotal++;
		break;
	case 8:
		pointCount[3]++;
		pointTotal++;
		break;
	case 9:
		pointCount[4]++;
		pointTotal++;
		break;
	case 10:
		pointCount[5]++;
		pointTotal++;
		break;
	}
	// ...
}

void Statistics::inputThrow(int dice1, int dice2, int point){
	//case win/lose/point
		//case of win/lose/point
	int roll = dice1 + dice2;

	totalThrow++;
	diceRoll[roll - 2]++; //index [0] -> dice roll of 2

	if(roll == 7){
		totalLoss++;
		pointLose++;
	} else if(roll == point){
		pointWin++;
		totalWin++;
		switch(point){
		case 4:
			pointWinLose[0]++;
			break;
		case 5:
			pointWinLose[1]++;
			break;
		case 6:
			pointWinLose[2]++;
			break;
		case 8:
			pointWinLose[3]++;
			break;
		case 9:
			pointWinLose[4]++;
			break;
		case 10:
			pointWinLose[5]++;
			break;
		}
	}
}

void Statistics::inputPtStrk(int streak){
	if(streak > longestPointRun) //set new pt streak
		longestPointRun = streak;
}

void Statistics::printReport(){
	// ...
	/* Craps		
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

	std::cout << std::setprecision(4) << " --- STATISTICS REPORT --- " << std::endl;
	std::cout << "Total Games: " << totalGame << std::endl;
	std::cout << "Games Won: " << double(totalWin)/totalGame*100 << "%" << std::endl;
	std::cout << "Games Lost: " << double(totalLoss)/totalGame*100 << "%" << std::endl;
	std::cout << std::endl;
	std::cout << "Won on First Throw: " << double(firstThrowWin)/totalGame*100 << "%" << std::endl;
	std::cout << "Lost on First Throw: " << double(firstThrowLoss)/totalGame*100 << "%" << std::endl;
	std::cout << "Point Obtained: " << double(pointTotal)/totalGame*100 << "%" << std::endl;
	std::cout << std::endl;
	std::cout << "Point of 4: " << double(pointCount[0])/totalGame*100 << "%" << " - Win Rate: " << double(pointWinLose[0])/pointTotal*100 << "% - Lose Rate: " << (100 - double(pointWinLose[0])/pointTotal*100) << "%" << std::endl;
	std::cout << "Point of 5: " << double(pointCount[1])/totalGame*100 << "%" << " - Win Rate: " << double(pointWinLose[1])/pointTotal*100 << "% - Lose Rate: " << (100 - double(pointWinLose[1])/pointTotal*100) << "%" << std::endl;
	std::cout << "Point of 6: " << double(pointCount[2])/totalGame*100 << "%" << " - Win Rate: " << double(pointWinLose[2])/pointTotal*100 << "% - Lose Rate: " << (100 - double(pointWinLose[2])/pointTotal*100) << "%" << std::endl;
	std::cout << "Point of 8: " << double(pointCount[3])/totalGame*100 << "%" << " - Win Rate: " << double(pointWinLose[3])/pointTotal*100 << "% - Lose Rate: " << (100 - double(pointWinLose[3])/pointTotal*100) << "%" << std::endl;
	std::cout << "Point of 9: " << double(pointCount[4])/totalGame*100 << "%" << " - Win Rate: " << double(pointWinLose[4])/pointTotal*100 << "% - Lose Rate: " << (100 - double(pointWinLose[4])/pointTotal*100) << "%" << std::endl;
	std::cout << "Point of 10: " << double(pointCount[5])/totalGame*100 << "%" << " - Win Rate: " << double(pointWinLose[5])/pointTotal*100 << "% - Lose Rate: " << (100 - double(pointWinLose[5])/pointTotal*100) << "%" << std::endl;
	std::cout << std::endl;
	std::cout << "Games with Point Won: " << double(pointWin)/pointTotal*100 << "%" << std::endl;
	std::cout << "Games with Point Lost: " << double(pointLose)/pointTotal*100 << "%" << std::endl;
	std::cout << std::endl;

	for(int i = 0; i < 11; i++){
		std::cout << "Percent Rolls of " << (i + 2) << ": " << double(diceRoll[i])/totalThrow*100 << "%" << std::endl;
	}
	std::cout << std::endl;
	std::cout << "Longest Point Run: " << longestPointRun << " consecutive point rolls." << std::endl << "(Scroll up to see rest of statistics)" << std::endl;
}