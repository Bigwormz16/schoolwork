//  FILE: permute.cpp
//  NAME: Ian Rosner
//  STUDENT ID: W1387836
//  Assignment 5
//  Purpose: implementation of Permute class as defined in
//			 permute.h (generates permutation of a string)
//  Notes: permutation() is executed upon object creation --
//         there is no need for the user to run permute.permutation()
//		   on their own, though it is guarded to handle it in the case
//		   that it happens.
#include "permute.h"
#include <string>
using namespace std;
/*
diagram of permutation functionality
given a string of ABC -->
	3 characters ->
		calculation of total permutations
		(factorial) 3! = 3 * 2 * 1 = 6

ABC swap 0, 0
|	ABC swap 1, 1
|	|	ABC swap 2, 2
|	|		ABC ---- END
|	ABC swap 1, 2
|		ACB swap 2, 2
|			ACB ---- END
|			
ABC swap 0, 1
|	BAC swap 1, 1
|	|	BAC swap 2, 2
|	|		BAC ---- END
|	BAC swap 1, 2
|		BCA swap 2, 2
|			BCA ---- END
|			
ABC swap 0, 2
	CBA swap 1, 1
	|	CBA swap 2, 2
	|		CBA ---- END
	CBA swap 1, 2
		CAB swap 2, 2
			CAB ---- END

3 main "threads" which swap first character
	2 nested "threads" which swap second character
		1 swap within which swaps 3rd character (end result)
		  3 * 2 * 1 -- 6 end results

*/

Permute::Permute(std::string s1, std::string s2)
{ //initialize variables, standard
	firstString = s1;
	secondString = s2;
	firstNode = NULL;
	lastNode = NULL;

	total = 0; //will later be calculated in permutation();
	permutation(); //all variables set up -- ready to start calculations!
}

Permute::~Permute()
{ //since we dynamically allocate memory
  //via a linked list to store strings,
  //a destructor is necessary
	Node *previous,
		 *current = firstNode;
	
	while(current != NULL)
	{ //iterate through list
		previous = current; //temporarily store to-be-deleted node
		current = current->link(); //advance in list
		delete previous; //delete last node
	}
}

void Permute::permutation()
{
	if (total > 0) //if total != 0, we have already generated
		return;
	else if (firstString == "" && secondString == "")
		return; //empty strings - no perm.
	else
		permutation(0);
}

void Permute::swap(int c1, int c2)
{ //simply exchanges the location of 2 characters in a string
	//ex: str = "abcd"; swap(str, 0, 3)
	//str now contains "dbca"
	char temp = firstString[c1]; //store away first char
    firstString[c1] = firstString[c2];
    firstString[c2] = temp;
}

void Permute::permutation(int currentPos)
{ //see header for detailed explanation
	if(currentPos == firstString.length()) //if all swaps in loop performed
	{ //we have a completed permutation
		firstNode = new Node(firstString, firstNode); //attach a new entry to node ladder
		if (total == 0) lastNode = firstNode; //set last node on first entry
		total++;
	}
	else //otherwise, continue generating permutations
	{
		for(int i = currentPos; i < firstString.length(); i++) //for all possible characters in currentPos
		{
			swap(currentPos, i); //try next possible character
			permutation(currentPos+1); //continue all the way to end of string
			swap(currentPos, i); //once we have reached the end,
		}							//undo last swap and return to last nest
	}								//then try a further character swap for currentPos
}

void Permute::print()
{
	Node *iter = firstNode; //iterator for traversing list

	//print header for object
	cout << "String 1 for this object is: " << firstString << endl;
	cout << "String 2 for this object is: " << secondString << endl;
	if (total > 0)
	{
		cout << "The total possible permutation is " << total << endl;
		if (total == 1)
			cout << "That is:"; //use correct grammar
		else
			cout << "They are:";
	}
	else
	{ //if total is 0
		cout << "There is no permutation." << endl;
	}

	//proceed to print out permutation list
	//print 4 per row if total < 100, otherwise 9
	short perRow = ((total < 100) ? 4 : 9);
	int count = -1;
	while(iter != NULL) //until end of list
	{
		count++;
		//insert new line on 4th / 9th entry
		if ((count % perRow) == 0) cout << endl;
		//80 is default console character width --just using tab now
		cout << iter->get() << secondString << '\t'; //print permutation

		iter = iter->link(); //advance list
	}
}