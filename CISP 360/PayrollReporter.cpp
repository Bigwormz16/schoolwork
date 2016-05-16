/* --PAYROLL REPORTER--
Ian Rosner
CISP360 Chapek - Write a program that calculates and outputs the
monthly paycheck information for an employee,
including all the amounts deducted from an employee’s
gross pay, and the net pay that is due to the employee. */
#include <iostream>
#include <iomanip> // precision, field length, fill, etc
#include <fstream> // file control
#include <sstream>
#include <string> // VS allegedly includes string in the iostream header but this is non-standard
#include <cctype> // validation with isalpha isdigit etc
using namespace std;

// ********* RATES **********
#define FED_TAX .15
#define STA_TAX .035
#define SOC_TAX .085
#define INSURANCE 75.00

string getName(); // get a valid name
float getPay(); // get a valid gross pay
void report(string name, float gross, ofstream *file); // report to screen and file
bool repeat(); // check if user wants to input another employee


int main(void)
{
	string empName;
	float grossPay;
	ofstream reportFile; // create file stream
	reportFile.open("report.txt"); // open our report file

	do {
		empName = getName();
		grossPay = getPay();
	
		report(empName, grossPay, &reportFile);

	} while(repeat()); // do this while repeat [== true]
	reportFile.close(); // close file
	cout << "Report file created and saved." << endl;
	system("pause");
}

string getName()
{
	bool checkName(string); // validation submodule
	string name;

	bool validName = false;
	while (!validName)
	{
		cout << "Enter employee's name (first and last)" << endl;
		fflush(stdin); // flush keyboard buffer for getline
		getline(cin,name);
		validName = checkName(name);
		cout << endl;
	}
	return name;
}

bool checkName(string name)
{
	for (int i = 0; i < (int)name.length(); i++) // length typecasted to avoid warning
	{
		if (!isalpha(name.at(i)) && name.at(i) != ' '){ cout << "Error: names may only contain letters or spaces!\n"; return false;} // if not alphabet character or space, return false
	}
	return true; // otherwise, return true
}

float getPay() // a truly beautiful module
{
	string payBuffer;
	float pay;
	bool validNum;

	do
	{
		validNum = true;
		cout << "Enter employee's gross pay:\n$";
		cin >> payBuffer;
		for (int i = 0; i < (int)payBuffer.length(); i++)
		{
			if (!isdigit(payBuffer[i]) && !(payBuffer[i] == '.' || payBuffer[i] == '-')) // if characters in buffer arent #s, AND not a . or a -
			{ // if isDigit for char is false AND char is not - OR .   (this took a lot of debugging for some reason)
				cout << "Error: non-numerical value entered!\n\n";
				validNum = false;
				break;
			}
		}
		if (validNum) // only do this if all is well so far
		{
			(stringstream)payBuffer >> pay; //typecast to stream, insert into pay var
			if(pay < 0) // check if negative
			{
				cout << "Error: pay value must be positive.\n\n";
				validNum = false;
			}
		}
	} while(!validNum); // do this until we get a valid number
	return pay;
}

void report(string name, float gross, ofstream *file) // do the reporting
{
	cout << fixed << setprecision(2) << endl << endl; // set formatting
	cout << name << endl;
	cout << setfill('.') << setw(26) << left << "Gross Amount: " << " $" << setfill(' ') << right << setw(8) << gross << endl;
	cout << setfill('.') << setw(26) << left << "Federal Tax: " << " $" << setfill(' ') << right << setw(8) << gross * FED_TAX << endl;
	cout << setfill('.') << setw(26) << left << "State Tax: " << " $" << setfill(' ') << right << setw(8) << gross * STA_TAX << endl;
	cout << setfill('.') << setw(26) << left << "Social Sec / Medicare: " << " $" << setfill(' ') << right << setw(8) << gross * SOC_TAX << endl;
	cout << setfill('.') << setw(26) << left << "Health Insurance: " << " $" << setfill(' ') << right << setw(8) << INSURANCE << endl;
	cout << setfill('.') << setw(26) << left << "Net Pay: " << " $" << setfill(' ') << right << setw(8) << (gross - (gross * (FED_TAX + STA_TAX + SOC_TAX)) - INSURANCE) << endl << endl << endl;
	// file report
	*file << fixed << setprecision(2); // set formatting
	*file << name << endl;
	*file << setfill('.') << setw(26) << left << "Gross Amount: " << " $" << setfill(' ') << right << setw(8) << gross << endl;
	*file << setfill('.') << setw(26) << left << "Federal Tax: " << " $" << setfill(' ') << right << setw(8) << gross * FED_TAX << endl;
	*file << setfill('.') << setw(26) << left << "State Tax: " << " $" << setfill(' ') << right << setw(8) << gross * STA_TAX << endl;
	*file << setfill('.') << setw(26) << left << "Social Sec / Medicare: " << " $" << setfill(' ') << right << setw(8) << gross * SOC_TAX << endl;
	*file << setfill('.') << setw(26) << left << "Health Insurance: " << " $" << setfill(' ') << right << setw(8) << INSURANCE << endl;
	*file << setfill('.') << setw(26) << left << "Net Pay: " << " $" << setfill(' ') << right << setw(8) << (gross - (gross * (FED_TAX + STA_TAX + SOC_TAX)) - INSURANCE) << endl << endl << endl;
}

bool repeat()
{
	char ans;
	cout << "Enter another employee? (Y / N)" << endl;
	cin >> ans;
	cout << endl;
	if (toupper(ans) == 'Y') return true; // only repeat if user enters y
	else return false;
}