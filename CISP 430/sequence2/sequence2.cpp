//  FILE: sequence2.cpp
//  NAME: Ian Rosner
//  STUDENT ID: W1387836
//  Assignment 2
/* Purpose: Sequence class implementation - container class which holds an ordered collection
	of items within a chunk of memory, sequenced via an internator iterator. */
/* Comments: created 2/7/14, finished 2/14/14. Uses assert() in remove_current()
	and current() to check preconditions. Implementation of sequence class as
	defined in sequence2.h.  */
/*--- END HEADER ---*/

#include "sequence2.h"
#include <cassert>

using namespace CISP430_A2;

// CONSTRUCTOR
sequence::sequence(size_type entry)
{
	//allocate a chunk of memory on the heap
	data = new value_type[entry];
	
	//initialize our values
	used = 0;
	capacity = entry;
	current_index = 0;
}

// COPY CONSTRUCTOR
sequence::sequence(const sequence& entry)
{
	//set values equal to that of entry's
	capacity = entry.capacity;
	used = entry.used;
	current_index = entry.current_index;

	//create heap chunk of equal size
	data = new value_type[capacity];
	for(int i = 0; i < used; i++)
	{ //copy data over to new sequence
		data[i] = entry.data[i];
	}
}

// Library facilities used: cstdlib
// MODIFICATION MEMBER FUNCTIONS
void sequence::start( )
{ //reset sequence to beginning item
	current_index = 0;
}

void sequence::advance( )
{ //increment index to point to next item in sequence
	current_index++;
}

void sequence::insert(const value_type& entry)
{
	if(used >= capacity) //ensure room for our insertion
		resize(size_t(capacity * 1.1)); //if resizing, increase size by 10%

	if(is_item()) //if current_index is a valid item:
	{ /*create an empty space at current_index by
		shifting items to the right by 1 */
		for(int i = used; i > current_index; i--)
		{
			data[i] = data[i-1];
		}
	}
	else
	{//no current item -> item inserted at front of seq.
		current_index = 0;
		//shift all items right by 1
		for(int i = used; i > 0; i--)
		{
			data[i] = data[i-1];
		}
	}
	//insert entry to our now-empty current_index
	data[current_index] = entry;
	used++; //one more item, one more used slot
}

void sequence::attach(const value_type& entry)
{
	if(used >= capacity) //ensure room for insertion
		resize(size_t(capacity * 1.1)); //10% size increase

	if(is_item()) //if current_index is a valid item:
	{
		current_index++; //insert entry AFTER current item
		//shift items to create an empty spot new entry
		for(int i = used; i > current_index; i--)
		{
			data[i] = data[i-1];
		}
	}
	else
	{/*no current item -> item inserted at back of sequence.
	   no shifting necessary! */
		current_index = used;
	}

	data[current_index] = entry; //place entry in now-empty spot
	used++; //one more item added to sequence
}

void sequence::remove_current( )
{
	assert(is_item() == true); //make sure there's an item to remove
	//shift items left by 1 to cover current_index
	for(int i = current_index; i < used-1; i++)
	{
		data[i] = data[i+1];
	}
	used--; //update used to reflect our changes
}

void sequence::resize(size_type new_capacity)
{ //Precondition: new_capacity > used
	if(new_capacity > used)
	{
		//allocate our new, larger chunk of memory
		value_type *temp = new value_type[new_capacity];

		//copy over contents of old chunk (manual copy)
		for(int i = 0; i < used; i++)
		{
			temp[i] = data[i];
		}

		delete [] data; //free space from original chunk
		data = temp;	//point data to new mem chunk
		capacity = new_capacity; //set capacity to reflect new size
	}
	//else -> condition not met, do nothing.
} // Postcondition: new space allocated and old space released

void sequence::operator =(const sequence &copySeq)
{
	resize(copySeq.capacity);

	used = copySeq.used; //copy over private variables
	current_index = copySeq.current_index;

	//perform manual copy of contents
	for(int i = 0; i < used; i++)
	{
		data[i] = copySeq.data[i];
	}
}

// CONSTANT MEMBER FUNCTIONS
sequence::size_type sequence::size( ) const
{ //returns number of used slots
	return used;
}

bool sequence::is_item( ) const
{ //check if index is extending past used slots (ternary operator)
	return (current_index < used) ? true : false;
}

sequence::value_type sequence::current( ) const
{ //Precondition: is_item( ) returns true.
	assert(is_item() == true);
	return data[current_index];
}

sequence::~sequence()
{ //deallocate heap chunk
	delete [] data;
}