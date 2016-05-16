#include <iostream>
#include <string>

/* Ian Rosner CISP360 Chapek 
8. Sum of Digits in a String
Write a program that asks the user to enter a series of single digit numbers with nothing
separating them. Read the input as a C-string or a string object. The program
should display the sum of all the single-digit numbers in the string. For example, if the
user enters 2514, the program should display 12, which is the sum of 2, 5, 1, and 4.
The program should also display the highest and lowest digits in the string.
*/

using namespace std;

bool validStr(string inStr);
int sumCalc(string inStr, int *minNum, int *maxNum);

int main(void)
{
	string myNum;
	int sumNum,
		minNum,
		maxNum;

	bool isValid = true;

	do
	{
		cout << "Please enter a series of single-digit numbers\n> ";
		cin >> myNum;

		isValid = validStr(myNum);
	} while (!isValid);

	sumNum = sumCalc(myNum, &minNum, &maxNum);

	cout << endl << endl;
	cout << "Sum of digits in string : " << sumNum << endl;
	cout << "Smallest digit in string: " << minNum << endl;
	cout << "Largest digit in string : " << maxNum << endl;
	system("pause");
}

bool validStr(string inStr)
{
	bool isValid = true;
	for(int k = 0; k < inStr.length(); k++)
	{
		if(!isdigit(inStr.at(k))) isValid = false;
	}
	if (!isValid) cout << "Error: non-digit in string.\n\n";
	return isValid;
}

int sumCalc(string inStr, int *minNum, int *maxNum)
{
	int length = inStr.length();
	int sum = 0;
	int temp;
	// initialization for min/max
	*maxNum = inStr.at(1) - 48;
	*minNum = inStr.at(1) - 48;

	for(int j = 0; j < length; j++)
	{
		temp = inStr.at(j) - '0';
		if(temp > *maxNum) *maxNum = temp;
		if(temp < *minNum) *minNum = temp;
		sum += temp;
	}
	return sum;
}