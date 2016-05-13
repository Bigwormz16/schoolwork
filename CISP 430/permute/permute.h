//  FILE: permute.h
//  NAME: Ian Rosner
//  STUDENT ID: W1387836
//  Assignment 5
//  Purpose: class which generates all possible permutations of a string
// Class overview: Node
/*	A basic Node implementation for a linked list
	Contains a constructor which is passed a string
		and another node to automatically link.
	Accessors: link() - returns pointer
			   get()  - returns data		*/

// Class overview: Permute
/*	A class which is passed two strings, generating
		all possible permutations of the first string,
		which are then stored within a linked list.
	Helper functions: swap() - exchanges 2 characters in a string
					  permutation() - wrapper for real permutation
									  function
									  */


#ifndef __PERMUTEA5__
#define __PERMUTEA5__

#include <iostream>

class Node
{
public:
	//constructor
	inline Node(std::string data, Node *p)
	{
		this->data = data;
		this->p = p;
	}
	inline Node *link(){ return p; }
	inline std::string get(){ return data; }
private:
	std::string data;
	Node *p;
};

class Permute
{
public:
	//constructor
	Permute(std::string s1, std::string s2);
	~Permute();
	void permutation();
	void print();
private:
	void swap(int c1, int c2); //exchanges two characters
	void permutation(int currentPos);
	Node *firstNode, //for linked list which stores permuted strings
		 *lastNode;
	std::string firstString,
				secondString;
	int total; //stores # of permutations (n!)
};
#endif //__PERMUTEA5__