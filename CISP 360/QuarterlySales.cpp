/*
Chapter 7, Challenge 7
Ian Rosner
CISP 360 Chapek

7. Quarterly Sales Statistics
Write a program that lets the user enter four quarterly sales gures for six divisions of
a company. The gures should be stored in a two-dimensional array. Once the gures
are entered, the program should display the following data for each quarter:
* A list of the sales figures by division
* Each division s increase or decrease from the previous quarter (This will not be
displayed for the first quarter.)
* The total sales for the quarter
* The company s increase or decrease from the previous quarter (This will not be
displayed for the first quarter.)
* The average sales for all divisions that quarter
* The division with the highest sales for that quarter
The program should be modular, with functions that calculate the statistics above.
Input Validation: Do not accept negative numbers for sales gures.

*/

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#define QTRCT 4 // quarter count
#define DVSCT 6 // division count

using namespace std;

void getInput(int qDivSales[][DVSCT]); // input collection
void printReport(int sales[][DVSCT]); // assembles report (this is where the magic happens)
float calcTotal(int arr[][DVSCT], int q); // gets sum of quarter
int getHighest(int arr[][DVSCT],int q); // picks highest division
string calcDiff(int a, int b); // finds difference

int main(void)
{
	int qDivSales[QTRCT][DVSCT]; // 4 quarters, 6 divisions

	getInput(qDivSales); //get (valid) inputs
	printReport(qDivSales); //do the rest
	system("pause");
}

void getInput(int qDivSales[][DVSCT])
{
	for(int j = 0; j < QTRCT; j++)
	{
		cout << "--- Enter Sales for Quarter " << j + 1 << " ---\n";
		for(int k = 0; k < DVSCT; k++)
		{
			cout << "Division " << k+1 << ": ";
			do cin >> qDivSales[j][k]; while(qDivSales[j][k] < 0);
		}
	}
	cout << endl;
}

void printReport(int sales[][DVSCT])
{
	cout << "Quarter 1 Review\n---Divisions---\n";
	for (int d = 0; d < DVSCT; d++) // first quarter print (no up / down in price)
	{
		cout << "Division " << d+1 << ": $" << setw(7) << left << sales[0][d] << endl;
	}
	cout << endl << "Highest Grossing Division: " << getHighest(sales,0) << endl << endl;
	cout << "Total gross sales:      $" << setw(7) << calcTotal(sales,0) << endl;
	cout << "Average division sales: $" << setw(7) << fixed << setprecision(2) << calcTotal(sales, 0)/DVSCT << endl << endl << endl;
	cout << setprecision(0);

	for (int q = 1; q < QTRCT; q++) // quarters 2 through 4
	{
		cout << "Quarter " << q+1 << " Review\n---Divisions---\n";
		for (int d = 0; d < DVSCT; d++)
		{
			cout << "Division " << d+1 << ": $" << setw(7) << left << sales[q][d] << calcDiff(sales[q][d],sales[q-1][d]) << endl;
		}
		
		cout << endl << "Highest Grossing Division: " << getHighest(sales,q) << endl << endl;
		cout << "Total gross sales:      $" << setw(7) << calcTotal(sales,q) << calcDiff(calcTotal(sales,q),calcTotal(sales,q-1)) << endl;
		cout << "Average division sales: $" << setw(7) << fixed << setprecision(2) << calcTotal(sales, q)/DVSCT << endl << endl << endl;
		cout << setprecision(0);
	}
	return;
}

float calcTotal(int arr[][DVSCT], int q)
{
	float sum = 0;

	for (int i = 0; i < DVSCT; i++)
	{
		sum += arr[q][i];
	}
	return sum;
}

int getHighest(int arr[][DVSCT],int q)
{
	int max = arr[q][0];
	int div = 1;
	for (int i = 0; i < DVSCT; i++)
	{
		if (arr[q][i] > max)
		{
			max = arr[q][i];
			div = i + 1;
		}
	}
	return div;
}

string calcDiff(int a, int b)
{
	string dif;
	ostringstream oss;

	if (a > b) oss << "[UP $" << (a-b) << "]";
	else if (a < b) oss << "[DOWN $" << (abs(a - b)) << "]";
	else oss << "[NO CHANGE FROM PREVIOUS QUARTER]";
	dif = oss.str();

	return dif;
}

/*
PROTOTYPE PRINT
Quarter 2 Review
Highest Grossing Divisions
1. Division G: $DVSCT0,000 [UP $30,000]
2. Division A: $20,000 [UP $15,000]
Total sales: $80,000 [UP $QTRCT5,000]
Average sales: $QTRCT0,000 [UP $30]
*/
	//list by division

	//division change

	//total sales

	//total sale change

	//average sale of divisions

	//highest sale division