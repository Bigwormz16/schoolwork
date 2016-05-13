
#ifndef H_H_CISP430V4Heade
#define H_H_CISP430V4Tail

#include <iostream>
#include <cassert>
 

template<class Type>
class queueType
{
private:
    void initializeQueue();
    void destroyQueue();
    bool isEmptyQueue();
    bool isFullQueue();
    void addQueue(const Type& queueElement);
    Type front();
    Type back();
    void deleteQueue();
    void queueType(int queueSize = 100); 
    ~queueType(); 
     void print();
     int getmaxQueueSize();

private:
    int maxQueueSize;
    int count;
    string *list;  	
     };



#endif