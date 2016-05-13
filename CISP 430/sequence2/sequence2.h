//  FILE: sequence1.h
//  NAME: Ian Rosner
//  STUDENT ID: W1387836
//  Assignment 2
/* Purpose: Sequence class header file - container class which holds an ordered collection
	of items within a chunk of memory, sequenced via an internator iterator. */
/* Comments: sequence2.h has not been modified from its original specification as
			 provided by Professor Huang. Implementation located in sequence2.cpp */
/*--- SPECIFICATION ---*/
// CLASS PROVIDED: sequence (part of the namespace CISP430_A2)
// There is no implementation file provided for this class since it is
// an exercise from Section 3.2 of "Data Structures and Other Objects Using C++"
//
// TYPEDEFS and MEMBER CONSTANTS for the sequence class:
//   typedef ____ value_type
//     sequence::value_type is the data type of the items in the sequence. It
//     may be any of the C++ built-in types (int, char, etc.), or a class with a
//     default constructor, an assignment operator, and a copy constructor.
//
//   typedef ____ size_type
//     sequence::size_type is the data type of any variable that keeps track of
//     how many items are in a sequence.
//
//   enum { CAPACITY = 30 };
//     CAPACITY is the maximum number of items that a sequence can hold.
//
// CONSTRUCTOR for the sequence class:
//   sequence(size_type entry=CAPACITY );
//     Postcondition: The sequence has been dynamic allocate memories.
//
//COPY CONSTRUCTOR
//   sequence(const sequence& entry)
//   Postcondition: The sequence has been created by copying from an existing sequence.
//
// MODIFICATION MEMBER FUNCTIONS for the sequence class:
//   void start( )
//     Postcondition: The first item on the sequence becomes the current item
//     (but if the sequence is empty, then there is no current item).
//
//   void advance( )
//     Precondition: is_item returns true.
//     Postcondition: If the current item was already the last item in the
//     sequence, then there is no longer any current item. Otherwise, the new
//     current item is the item immediately after the original current item.
//
//   void insert(const value_type& entry)
//     Precondition: size( ) < CAPACITY. if this is not true then increase the capacity by 10%
//     Postcondition: A new copy of entry has been inserted in the sequence
//     before the current item. If there was no current item, then the new entry 
//     has been inserted at the front of the sequence. In either case, the newly
//     inserted item is now the current item of the sequence.
//
//   void attach(const value_type& entry)
//     Precondition: size( ) < CAPACITY.if this is not true then increase the capacity by 10%
//     Postcondition: A new copy of entry has been inserted in the sequence after
//     the current item. If there was no current item, then the new entry has 
//     been attached to the end of the sequence. In either case, the newly
//     inserted item is now the current item of the sequence.
//
//   void remove_current( )
//     Precondition: is_item returns true.
//     Postcondition: The current item has been removed from the sequence, and the
//     item after this (if there is one) is now the new current item.
//
//Operator= overloading
//   void sequence::operator =(const sequence&);
//     Postcondition:  The l-value's sequence object is copy to the r-value
//
// CONSTANT MEMBER FUNCTIONS for the sequence class:
//   size_type size( ) const
//     Postcondition: The return value is the number of items in the sequence.
//
//   bool is_item( ) const
//     Postcondition: A true return value indicates that there is a valid
//     "current" item that may be retrieved by activating the current
//     member function (listed below). A false return value indicates that
//     there is no valid current item.
//
//   value_type current( ) const
//     Precondition: is_item( ) returns true.
//     Postcondition: The item returned is the current item in the sequence.
// Destructor
//	 ~sequence()  
//     Postcondition: release the memory to the heap
//
// VALUE SEMANTICS for the sequence class:
//    Assignments and the copy constructor may be used with sequence objects.
//
//void resize(size_type new_capacity )
//Precondition: new_capacity > used
// Postcondition: new space allocated and old space released
   

#ifndef SEQUENCE_H
#define SEQUENCE_H
#include <cstdlib>  // Provides size_t

namespace CISP430_A2
{
    class sequence
    {
    public:
        // TYPEDEFS and MEMBER CONSTANTS
        typedef double value_type;
        typedef size_t size_type;
        enum { CAPACITY = 30 };
        // CONSTRUCTOR
        sequence(size_type entry=CAPACITY );
		   // COPY CONSTRUCTOR
        sequence(const sequence& entry)   ;       
    // Library facilities used: cstdlib
        // MODIFICATION MEMBER FUNCTIONS
        void start( );
        void advance( );
        void insert(const value_type& entry);
        void attach(const value_type& entry);
        void remove_current( );
		void resize(size_type );
		void sequence::operator =(const sequence&);
        // CONSTANT MEMBER FUNCTIONS
        size_type size( ) const;
        bool is_item( ) const;
        value_type current( ) const;
		//Destructor
		 ~sequence()  ;
    private:
        value_type *data;
        size_type used;
		size_type capacity;
        size_type current_index;
    };
}

#endif

