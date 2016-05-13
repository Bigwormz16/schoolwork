//  FILE: CISP430V4A6.cpp
//  NAME: Ian Rosner
//  STUDENT ID: W1387836
//  Assignment 6
//  Purpose: driver file to showcase implementation of table

/* SPECIFICATION:
 CISP430V4A6.cpp is the driver for this assignment and there are several steps you need to do to test the program.
 Instantiate two Table objects and each with 10 fields.
 Display the two Table objects’ information.
 Use random number generator to generate 70 numbers each in between 0~200 for the Table objects.
 Display the two Table objects’ information.
 Removes all the data in first object.
 Display the two Table objects’ information.
 Using = to assign 2nd object to the first one.
 Display the two Table objects’ information. */

#include <iostream>
#include "table2.h"
#include "link2.h"

using namespace std;

struct GenericRecord
{
	double data;
	int key;
};

void printTables(table<GenericRecord> t1, table<GenericRecord> t2);

int main()
{
	/* Instantiate two Table objects and each with 10 fields. */
	table<GenericRecord> table1, table2;
	GenericRecord record;

	/* Display the two Table objects’ information. */
    cout << "Instantiate two Table objects." << endl << endl;
	printTables(table1, table2);

	/* Use random number generator to generate 70 numbers
	each in between 0~200 for the Table objects. */
    cout << endl << "**Using random number generator generates 70 numbers for the objects.**" << endl << endl;
    
    record.data = 2.5;
	for(int i = 0; i < 70; i++)
	{ //fill our tables with random numbers (0 - 199)
		record.key = rand() % 201;
        table1.insert(record);
        record.key = rand() % 201;
        table2.insert(record);
	}

	/* Display the two Table objects’ information. */
	printTables(table1, table2);

	/* Removes all the data in first object. */
    cout << endl << "**Calling clear function to clear all contents of first object.**" << endl << endl;
	table1.clear();
    
	/* Display the two Table objects’ information. */
	printTables(table1, table2);

	/* Using = to assign 2nd object to the first one. */
    cout << endl << "**Using table1 = table2 displays the assignment operator overloading.**" << endl << endl;
	table1 = table2;

	/* Display the two Table objects’ information. */
	printTables(table1, table2);
    
	system("pause");
	//cout << endl << "Press enter key to continue . . . "; //non-windows end
	//fflush(stdin);
	//getchar();
}

void printTables(table<GenericRecord> t1, table<GenericRecord> t2)
{
	/* Display the two Table objects’ information. */
	cout << "\t\tTotal records in the first Table object is " << t1.size();
	cout << endl << "\t\tContains of the first object display at below: " << endl;

	for(int i = 0; i < 10; i++)
	{
		t1.print(i);
	}

	cout << "-------------------------------------------" << endl;
	cout << "\t\tTotal records in the second Table object is " << t2.size();
	cout << endl << "\t\tContains of the second object display at below: " << endl;

	for(int i = 0; i < 10; i++)
	{
		t2.print(i);
	}
    
	cout << "===========================================" << endl;
}