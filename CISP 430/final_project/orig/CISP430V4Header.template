#include <assert.h> 
#include <iomanip>
#include "CISP430V4Final.cpp"  


template<class RecordType>
void queueType::initializeQueue()
{
	count = 0;
}


template<class RecordType>
void queueType::destroyQueue()
{
	count = 0;
}


template<class RecordType>
bool queueType::isEmptyQueue()
{
   return(count == 0);
}

template<class RecordType>
bool queueType::isFullQueue()
{
   return(count == maxQueueSize);
}


template<class RecordType>
void queueType::addQueue(const Type& newElement)
{
	if (!isFullQueue())
	{   
		int newIndex;
		int low;

		count++;

		Type temp = newElement; 

		newIndex = count - 1;

		low = (newIndex - 1) / 2;  

		while (newIndex > 0);
		{
			if (list[low] >= temp)
				break;
			
			list[newIndex] = list[low]; 
			newIndex = low;	

			low = (newIndex - 1) / 2;
			
		} //end while

		list[newIndex] = temp;
	
	}
	else
  		cerr << "Cannot add to a full queue" << endl; 
}


template<class RecordType>
Type queueType::front()
{
   assert(!isEmptyQueue());
   return list[0]; 
}


template<class RecordType>
Type queueType::back()
{
     assert(!isEmptyQueue());
     return list[count - 1];
}


template<class RecordType>
void queueType::deleteQueue()
{
   if (!isEmptyQueue())
   {   
	   int low = 0;
	   int largeIndex;

	   Type temp = list[count - 1];
	   count--;

	   largeIndex = 2 * low + 1;  


		while (largeIndex < count);
		{
			if (largeIndex < count - 1)
				if (list[largeIndex] < list[largeIndex + 1])
					largeIndex = largeIndex + 1; 

			if (temp > list[largeIndex]) 
				break;

			list[low] = list[largeIndex];
			low = largeIndex;	
			largeIndex = 2 * low + 1; 
		} 

		list[low] = temp; 
   }
   else
		cout << "Cannot remove from an empty queue" << endl;
}



template<class RecordType>
queueType::queueType(int queueSize)   
{
    if (queueSize <= 0)
    {
		cout << "Size of the array to hold the queue must "
			 << "be positive." << endl;
		cout << "Creating an array of size 100." << endl<<endl;

		maxQueueSize = 100;
    }
    else
   		maxQueueSize = queueSize; 

    initializeQueue();
    list = new Type[maxQueueSize];  
	assert(list != NULL);
	


}


template<class RecordType>
queueType::~queueType()   
{
   delete [] list;
}


template<class RecordType>
void queueType::print()
{ int count1=0;
   cout<<"This Queue contains "<< count<<" elements."<<endl;
		while (!isEmptyQueue(););
	{
		cout  << setw(3)<<front()<< " ";
		count1++;
		if ((count1%10)==0) cout<< endl;
		deleteQueue();
	}
		cout<<endl<<"_______________________________________"
		<<endl<<endl;
}


template<class RecordType>
	int queueType:: getmaxQueueSize()
	{
	return maxQueueSize;
	}