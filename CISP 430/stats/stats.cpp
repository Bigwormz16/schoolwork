//  stats.cpp
//	Name: Ian Rosner W1387836
//	Program Assignment #1
//	Purpose: statistician class implementation
//	Date: 1/26/2014

#include "stats.h"
#include <assert.h>

using namespace CISP430_A1;

//class statistician
statistician::statistician() // default constructor
{
	count = 0;
	total = 0;
}

// MODIFICATION MEMBER FUNCTIONS
void statistician::next(double r)
{
	if (count == 0) // first added item, set min/max
	{
		tiniest = r;
		largest = r;
	}
	else // check if r is a min or max number
	{
		if (r > largest) largest = r;
		if (r < tiniest) tiniest = r;
	}
	total += r; // add 'next' item to sum
	count++;
}

void statistician::reset( )
{
	count = 0;
	total = 0;
	// no need to reset tiniest/largest
	// resetting count will take care of this
}

// CONSTANT MEMBER FUNCTIONS
//int length( ) const { return count; }
//double sum( ) const { return total; }
double statistician::mean( ) const
{ // PRECONDITION: count > 0
	assert(length() > 0);
	return total / count;
}

double statistician::minimum( ) const
{ // PRECONDITION: count > 0
	assert(length() > 0); // 
	return tiniest;
}

double statistician::maximum( ) const
{ // PRECONDITION: count > 0
	assert(length() > 0);
	return largest;
}

// FRIEND FUNCTIONS
statistician CISP430_A1::operator + (const statistician& s1, const statistician& s2)
{
	// check if s1 or s2 have a count of 0
	// if so, return the other value
	// since adding 0 will have no affect
	if (s1.count == 0) return s2;
	if (s2.count == 0) return s1;

	//otherwise, add total and count,
	//and set correct min/max
	statistician temp;
	temp.total = s1.total + s2.total;
	temp.count = s1.count + s2.count;

	//set temp.tiniest to the smaller of s1.tiniest and s2.tiniest (ternary operator)
	temp.tiniest = ((s1.tiniest <= s2.tiniest) ? s1.tiniest : s2.tiniest);
	//set temp.largest to the larger of s1.largest and s2.largest (ternary operator)
	temp.largest = ((s1.largest >= s2.largest) ? s1.largest : s2.largest);
	
	return temp;
}

statistician CISP430_A1::operator * (double scale, const statistician& s)
{
	statistician temp = s;
	temp.total *= scale;
	temp.tiniest *= scale;
	temp.largest *= scale;

	// after multiplying by a negative, ensure our min/max are correct
	if (temp.tiniest > temp.largest)
	{
		double swap = temp.largest;
		temp.largest = temp.tiniest;
		temp.tiniest = swap;
	}

	return temp;
}

// NON-MEMBER functions for the statistician class
bool CISP430_A1::operator ==(const statistician& s1, const statistician& s2)
{ // non-member -- need to use public methods
	if ((s1.sum() == 0 && s2.sum() == 0) && (s1.length() == 0 && s2.length() == 0))
	{ // first check if objects are in initial/reset state
		return true;
	}
	else if ((s1.sum() != s2.sum()) || (s1.length() != s2.length()) || (s1.maximum() != s2.maximum()) || (s1.minimum() != s2.minimum()))
	{ // if any private member of s1 is not equal to s2, return false
		return false;
	}

	// otherwise, they are equal -- return true
	return true;
}