// NAME: Ian Rosner
// CLASS: CISP430 Spring 2014 Huang
// STUDENT ID: W1387836
// Purpose: a circular array queue
/* CHANGES:
	1. headerguard fixed
	2. template class changed to RecordType
	3. constructor and destructor fixed
	4. destroyQueue() changed to clear
	5. first 'private:' changed to 'public:'
	6. initializeQueue() removed, already have contructor
	7. deleteQueue() removed, already have destructor
	8. added first and last private member data
	9. added next_index() helper function
	10. added template implementation include
*/
// FUNCTION: queueType()
// Purpose: initialize a queueType object. If no parameter is given,
// 	    defaults to 100 slots of storage.
// Postconidition: a new queueType object has been initialized.

// FUNCTION: ~queueType()
// Purpose: releases allocated memory to the heap.
// Postcondition: object has been destructed, memory released.

// FUNCTION: clear()
// Purpose: resets a queueType to default state
// Postcondition: queueType has been reset.

// FUNCTION: isEmptyQueue()
// Purpose: determines whether the queue is empty or if it has items.
// Postcondition: returns true if empty, false if queue contains items.

// FUNCTION: isFullQueue()
// Purpose: determines whether the queue is full, or if it has room.
// Postcondition: returns true if there is no more room for items in the queue.

// FUNCTION: push(item)
// Purpose: inserts item to the back of the queue
// Precondition: queue is not full
// Postcondition: item has been inserted at the back of the queue.

// FUNCTION: pop()
// Purpose: removes an item from the front of the queue.
// Precondition: queue is not empty.
// Postcondition: item has been removed from front of queue

// FUNCTION: front()
// Purpose: obtain the item at the front of the queue
// Precondition: queue is not empty.
// Postcondition: item has been returned as type RecordType

// FUNCTION: back()
// Purpose: obtain the item at the back of the queue
// Precondition: queue is not empty.
// Postcondition: last item has been returned as type RecordType

// FUNCTION: print()
// Purpose: displays the contents of a queue.
// Precondition: queue is not empty
// Postcondition: contents of the queue have been printed to the screen.

// FUNCTION: getMaxQueueSize()
// Purpose: returns the capacity of the queue
// Postcondition: maxQueueSize has been returned

// FUNCTION: next_index(i)
// Purpose: determine where the next slot for insertion is
// Postcondition: next slot for insertion has been returned.
// Note: used to implement circular array -- wraps if last is equal to maxQueueSize

#ifndef H_H_CISP430V4H //1. FIXED
#define H_H_CISP430V4H

#include <iostream>
#include <cassert>


template<class RecordType> //2. changed from <class Type>
class queueType
{
public:
	queueType(int queueSize = 100); //3. removed void, moved to top
	~queueType(); //moved to top
	//void initializeQueue(); //6. removed (constructor)
	void clear();
	bool isEmptyQueue();
	bool isFullQueue();
	void push(const RecordType& queueElement); //11. renamed to push
	RecordType front();
	RecordType back();
	void pop(); //renamed to pop
	void print();
	int getmaxQueueSize();
private:
	int next_index(int i); //9. added
	int maxQueueSize;
	int count;
	int first; //8. added - stores index of first item in queue
	int last;  //8. added - stores index of last item
	RecordType *list; //changed to RecordType from string
};

#include "CISP430V4Header.template" //10. attach template implementation to header

#endif //END HEADER