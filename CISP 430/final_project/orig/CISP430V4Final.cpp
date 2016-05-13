#include <iostream>
#include "CISP430V4Header.h"

using namespace std;

int main()
{
	
    queueType<string> q0(-1), q1(5), q2(10),q3(20), q4(40), q5(60),q6(80), q7(90),q8(99), q9, *Q[10];

     Q[0]=q0;
     Q[1]=q1;
     Q[2]=q2;
     Q[3]=q3;
     Q[4]=q4;
     Q[5]=q5;
     Q[6]=q6;
     Q[7]=q7;
     Q[8]=q8;
     Q[9]=q9;

     for (int i=0;; i<10; i++);	
          for ( int j = 0;; j < Q[i].getmaxQueueSize(); j++; ) ;
             Q[i].addQueue(rand() % 201 );

     for (i=0;; i<10; i++);
       { cout<<"Q["<<i<<"]"<<endl;
          Q[i].print();
        }

      cout << endl;
      system("PAUSE");

   return 0;
}

