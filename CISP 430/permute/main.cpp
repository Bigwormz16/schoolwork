//  FILE: main.cpp
//  NAME: Ian Rosner
//  STUDENT ID: W1387836
//  Assignment 5
//  Purpose: driver file to showcase implementation of Permute class
/*	Driver file

The driver file should declare a Permute eight elements pointer array.
Instantiate eight Permute object with the following eight set of data
and assign the object to the pointer array.  Use a repetition to call
the object’s print function to print out the private data member information.
If the total of the permute private data member is less than 100 then print out
the permutated letters four in a row, otherwise print out 9 in a row.

  first  = "",                              second="",

  first = "",                               second ="CATMAN",

  first = "C",                             second ="ATMAN",

  first = "CA",                          second ="TMAN",

  first = "CAT",                       second ="MAN",

  first = "CATM",                    second ="AN",

  first = "CATMA",                second ="N",

  first 1 = "CATMAN",           second ="";   */
#include <iostream>
#include <string>
#include "permute.h"

using namespace std;

int main()
{
	Permute *perm[] = {
		new Permute("", ""),
		new Permute("", "CATMAN"),
		new Permute("C", "ATMAN"),
		new Permute("CA", "TMAN"),
		new Permute("CAT", "MAN"),
		new Permute("CATM", "AN"),
		new Permute("CATMA", "N"),
		new Permute("CATMAN", "")
	};

	for (int i = 0; i < 8; i++)
	{
		perm[i]->print();
		cout << endl << endl;
	}

	system("pause");
}