/* Ian Rosner CISP360
   Fix Program #1


*/
#include <iostream>

using namespace std; // added
                   
int sum(int [], int); // first param is now array
int countNmbrsBigger(int [], int, int);
float average(int [], int); // switched to float for decimal pt value
int high(int [], int);
int low(int [], int);
int find(int [], int, int);


int main(void)
{
	const int arraySize = 10; // 10 nums in array 
	int theArray[arraySize] = {1, 5, 25, 10, 12, 9, 24, 24, 22, 2}; 

	cout << "Sum: " << sum(theArray, arraySize) << endl; //added <<
	cout << "Count of numbers bigger than 10: " << countNmbrsBigger(theArray, arraySize, 10) << endl;  
	cout << "Average: " << average(theArray, arraySize) << endl;
	cout << "High: " << high(theArray, arraySize) << endl;
	cout << "Low: " << low(theArray, arraySize) << endl;
	cout << "Find: " << find(theArray, arraySize, 25) << endl;
	cout << "Find: " << find(theArray, arraySize, 100) << endl;
	system("pause");
} 


int sum(int theArray [], int theArraySize){
	
	int theSum = 0;
	for (int i = 0; i < theArraySize; i++)
	{ // changed <= to <
		theSum += theArray[i];
	}
	return theSum;
}

int countNmbrsBigger(int theArray [], int theArraySize, int Number){
	int theCount = 0;
	for (int i = 0; i < theArraySize; i++)
	{
		if (theArray[i] > Number)
		{
		   theCount++; // add one instead of 5
		}
	}
	return theCount;
}

float average(int theArray [], int theArraySize)
{
	int theSum = 0;
	for (int i = 0; i < theArraySize; i++)
	{ //Changed > to <
		theSum += theArray[i];
	}
	return (float)theSum/theArraySize; // changed + to / and typecasted to float for decimal
}

int high(int theArray [], int theArraySize)
{
	int HighValue = theArray[0];
	for (int i = 0; i < theArraySize; i++)
	{ // <= to <
		if (theArray[i] > HighValue){
			HighValue = theArray[i];
		}
	}
	return HighValue;
}

int low(int theArray [], int theArraySize)
{
	int lowValue = theArray[0];
	for (int i = 0; i < theArraySize; i++){
		if (theArray[i] < lowValue){
			lowValue = theArray[i];
		}
	}
	return lowValue;
}

int find(int theArray [], int theArraySize, int theNumber)
{
	int theSubscript = -1;
	for (int i = 0; i < theArraySize; i++)
	{
		if (theArray[i] == theNumber)
		{ // double equals
			theSubscript = i;
		}
	}
	return theSubscript;
}