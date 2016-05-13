//  FILE: pqueue1.cpp
//  NAME: Ian Rosner
//  STUDENT ID: W1387836
//  Assignment 4
/* Purpose: Priority Queue class implementation using a linked list, as defined in pqueue1.h
			Items are stored in order of priority, and the highest item is popped off the queue.
/* Comments: created February 2014. Implementation of PriorityQueue class as defined in pqueue1.h.

	Values are stored in order of priority when insert()-ed.
	---HIGHER PRIORITY ITEMS COME FIRST---
		an item of priority 10 will come
		before an item of priority 1

	NOT a templated implementation, 'Item' typedef in pqueue1.h
	must be changed	manually. Currently set to int type.	*/
//------- END HEADER -------

#include "pqueue1.h"

//DEFAULT CONSTRUCTOR
PriorityQueue::PriorityQueue( )
{ //initialize pQueue with 0 items
	many_nodes = 0;
	head_ptr = NULL;
} //Postcondition: The PriorityQueue has been initialized with no Items.

//COPY CONSTRUCTOR
PriorityQueue::PriorityQueue(const PriorityQueue& source)
{
	if (source.head_ptr == NULL)
	{ //empty case
		head_ptr = NULL;
		many_nodes = 0;
	}
	else
	{
		head_ptr = new Node; //create new list
		head_ptr->link = NULL;

		Node *iter = head_ptr, //iterator for *this
			 *sIter = source.head_ptr; //source iterator

		for (int i = 0; i < source.many_nodes - 1; i++)
		{ //copy values for current item
			iter->data = sIter->data;
			iter->priority = sIter->priority;
		
			iter->link = new Node; //create next node for new queue
			iter = iter->link; //advance for next copy
			sIter = sIter->link;
		}
		//at this point, we are at the tail end
		//so we do not create a new node
		iter->data = sIter->data; //copy values
		iter->priority = sIter->priority;
		iter->link = NULL; //tail end of queue
	}
	
	many_nodes = source.many_nodes;
}

//DESTRUCTOR
PriorityQueue::~PriorityQueue( )
{ //deallocate heap memory
	Node *previous,
			*current = head_ptr;
	
	while(current != NULL)
	{ //iterate through list
		previous = current; //temporarily store to-be-deleted node
		current = current->link; //advance in list
		delete previous; //delete last node
	}
}

void PriorityQueue::operator =(const PriorityQueue& source)
{
	//self-assignment case:
	if (this == &source) return;
	

	//deallocate queue
	Node *sIter, //second iterator / source iterator
		  *iter = head_ptr; //*this iterator

	while(iter != NULL)
	{ //deallocate original queue
		sIter = iter;
		iter = iter->link;
		delete sIter;
	}

	if (source.head_ptr == NULL)
	{ //reset head_ptr
		head_ptr = NULL;
	}
	else
	{
		iter = head_ptr = new Node;
		sIter = source.head_ptr;

		//rebuild queue, copying values from source
		for (int i = 0; i < source.many_nodes - 1; i++)
		{ //copy values for current item
			iter->data = sIter->data;
			iter->priority = sIter->priority;
		
			iter->link = new Node; //create next node for new queue
			iter = iter->link; //advance for next copy
			sIter = sIter->link;
		}
		//at this point, we are at the tail end
		//so we do not create a new node
		iter->data = sIter->data; //copy values
		iter->priority = sIter->priority;
		iter->link = NULL; //tail end of queue
	}

	many_nodes = source.many_nodes;
}

void PriorityQueue::insert(const Item& entry, unsigned int priority)
{
	Node *iter = head_ptr,  //stores node after inserted node
		 *previous = NULL,  //stores node before inserted node
		 *temp;				//stores inserted node

	//iterate through, checking priority until we find
	//the correct place to insert our new item
	while ((iter != NULL) && (priority <= iter->priority)) //check null first so iter->priority doesnt crash
	{
		previous = iter;
		iter = iter->link;
	}

	/* END CASES:
		1. iter == NULL && previous != NULL - insert at tail [standard insert]
		2. iter == NULL && previous == NULL - no head exists, create one
		3. iter != NULL && previous == NULL - insert before head
		4. iter != NULL - insert after previous [standard insert]		*/
	
	//all we do within this block is create the node and link it,
	//storing the address of the new node in temp
	//values are set *afterwards*
	if (previous == NULL)
	{ 
		if (iter = NULL)
		{ //case 2: create head
			head_ptr = new Node;
			head_ptr->link = NULL;
			temp = head_ptr;
		}
		else
		{ //case 3: insert before head
			previous = new Node;
			previous->link = head_ptr;
			head_ptr = previous;
			temp = head_ptr;
		}
	}
	else
	{ //cases 1 & 4: standard insert
		temp = new Node;
		previous->link = temp;
		temp->link = iter;
	}
	//temp stores new node, already linked
	//now set its values
	temp->data = entry;
	temp->priority = priority;
	many_nodes++;
} //Postcondition: A new copy of entry has been inserted with the specified
  //priority.

PriorityQueue::Item PriorityQueue::get_front( )
{ //Precondition: size( ) > 0.
	if (many_nodes > 0)
	{
		Node *temp = head_ptr;
		
		head_ptr = head_ptr->link; //set new head of list
		Item frontItem = temp->data; //save data field for returning
		
		delete temp; //deallocate memory
		many_nodes--; //one item less in queue
		return frontItem; //return data
	}
} //The highest priority item has been returned and has been
//     removed from the PriorityQueue.