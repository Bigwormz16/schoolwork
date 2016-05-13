#pragma once
#include <iostream>
#include <iomanip>

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

class Statistics { //class to collect our statistics of dice rolls
private:
	int totalThrow, totalGame;
	
	int totalWin, totalLoss; //overall win loss pctg
	int firstThrowWin; //pctg win on first throw
	int firstThrowLoss; //pctg lose on first throw
	int pointTotal; //pctg get a point	
	int pointCount[6]; //pctg for point of 4, 5, 6, 8, 9, 10
	int pointWinLose[6]; //point of 4 - 10 pctg win lose
	//int pointOther; //all other points
	int pointWin, pointLose; //win lose pctg with a point
	int diceRoll[11]; //pctg of time roll of dice 2-12 2-1, 3-2, 4-3, 5-4, 6-5, 7-6, 8-7, 9-8, 10-9, 11-10, 12-11
	int longestPointRun; //longest run with a point

public:
	Statistics(); //constructor
	void inputFirstThrow(int dice1, int dice2); //collect info for roll 1
	void inputThrow(int dice1, int dice2, int point); //for subsequent throws
	void inputPtStrk(int streak);
	void printReport();
};