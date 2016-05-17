An [almost?] fully-complete archive of the code that I've written for school over the years.  
*work in progress - still working on cleaning up files/folders & writing descriptions for each project!
TODO: write descriptions for 140

# Table of Contents  
* [CISP 301](#c301)

* [CISP 360](#c360)

* [CISP 310](#c310)

* [CISP 400](#c400)

* [CISP 430](#c430)

* [CISP 440](#c440)

---
* [ECS 154a](#e154)

* [ECS 140a](#e140)

* [ECS 127](#e127)

---

## <a name="c301"></a>CISP 301 - Algorithm Design and Implementation  
The first programming class I ever took.  
Contents include iterative revisions of a program lovingly known as the "payroll reporter."  



## <a name="c360"></a>CISP 360 - Intro to Structured Programming  
*[grouped with partners for some assignments]*  
	
	challenges - group project: various challenges listed in the book, mostly small calculators  
				 examples include: calculate amount of slices in a pizza, monthly interest calculator,  
				 calorie calculator, monthly payments to pay off loans, box office profit calculator  
				 (22 applets in total)

	rainfall - collects statistics about monthly rainfall  
			   average rainfall, total rainfall, least rainfall, most rainfall  

	temperature [group] - a temperature converter  

	DigitsInStrings - sums the single-digit numbers occurring in a string  

	FinalFix[1|2] - assignment was to fix the bugs in given programs (included for completeness)  

	PassByReference - small program to demonstrate output via passing an address  

	PayrollReporter - the good ol' payroll reporter! [see: cisp 301]  

	QuarterlySales - quarterly sales calculator a business with various divisions  



## <a name="c310"></a>CISP 310 - Assembly Language Programming for Microcomputers  
Fairly sloppy assembly code. Very fun class, though!

	10mult - input two numbers of up to ten digits each, outputs the product

	anim - the final project was to create an animation
		   my animation features a cow grazing in a pasture.. when trouble strikes!
		   [link]

	bubsort - fills up an array with random numbers and runs a bubblesort on it

	celsius2farenheit - a simple temperature converter

	encode - 
	decode - 

	dow - enter a date & the program will tell you what day of the week it lands on, taking into account leap years.

	fibonacci - calculates the nth fibonacci number, up to 72-digit numbers. detects overflow.

	marb [marbles] - marbles experiment
		ends up generating primes

	parity

	ulam - ulam/collatz conjecture



## <a name="c400"></a>CISP 400 - Object Oriented Programming with C++
**Coming soon!**  
Taught by the same professor as 301, this course took an iterative approach on a dictionary application.  


## <a name="c430"></a>CISP 430 - Data Structures  
	A1:   
	A2: implementation of a sequence  
	A3: implementation of a sequence using a linked list  
	A4: implementation of a priority queue using a linked list  
	A5: a permutation-generating class which permutes a string  
	A6:   
	FINAL: code written for final exam ?, circular array  

## CISP <a name="c440"></a>440 - Discrete Structures for Computer Science  
	permutations: shows all permutations or combinations of an entered number

	craps: statistical analysis of the game of craps

	3card: statistical analysis of the Three Card problem (aka the Monty Hall problem) - takes samples using various strategies and reports the win rate

	graph: checks if two graphs are isomorphic - if so, display the bijection

---

## <a name="e154"></a>ECS 154a

	**You are to implement two caches for a simulated RAM that has 16-bit addresses, and is byte addressable. Both caches will have block sizes of 8 bytes, and a total capacity of 512 bytes.**  
	See pdf for more details on this assignment!  

	dmcache: a simulation of a directly-mapped cache

	sacache: a simulation of a four-way set associative cache

	vm: a virtual memory page replacement simulator


## <a name="e140"></a>ECS 140a
**Coming soon!**  
[java, lisp, prolog]  
todo: write descriptions

## <a name="e127"></a>ECS 127
	
	substitution_solver: cracks a substitution cipher using the
						 frequencies of two-letter pairs occurring
						 in a corupus text (in this case, we used
						 the novel "War and Peace")

	rc4_bias: demonstrates how the rc4 stream cipher has a bias in that
			  the second byte that it outputs is approximately twice as
			  likely to be 0 than any other value.
