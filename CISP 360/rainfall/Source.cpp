/*	Name: Ian Rosner
	Assignment: CH8 Challenge 5
	CISP360 Chapek 

collect statistics about rainfall through the months
(total, average, highest, lowest, sorted high to low)

*/

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

void bubbleSort(int arr[], int n, string month[]) { // bubble sort algorithm taken from algolist.net, modified
      bool swapped = true;
      int j = 0;
      int tmp;
	  string tmpMonth;

      while (swapped) {
            swapped = false;
            j++;
            for (int i = 0; i < n - j; i++) {
                  if (arr[i] < arr[i + 1]) {
                        tmp = arr[i];
						tmpMonth = month[i];
                        arr[i] = arr[i + 1];
						month[i] = month[i + 1];
                        arr[i + 1] = tmp;
						month[i + 1] = tmpMonth;
                        swapped = true;
                  }
            }
      }
}

int main()
{
		const int SIZE = 12;
		int rainfall[SIZE];
		string month[] = {"January", "February", "March", "April", // month array containing names
						"May", "June", "July", "August",
						"September", "October", "November",
						"December"};
                        
		double sum = 0;
		double min = 0;
		double max = 0;
  
		for(int i = 0; i < SIZE; i++)
		{
			cout << "Enter the rainfall for the month of " << setw(10) << left << month[i] << " "; // NOW READS FROM OUR MONTH ARRAY
			cin >> rainfall[i];
			if(rainfall[i] < 0)
			{
					cout << "Invalid rainfall! ";
					cout << "Enter the rainfall for month " << month[i] << "\t";
					cin >> rainfall[i];
			}
		}
		system("cls"); // clear screen for output
		sum = 0;
		for(int x = 0; x < SIZE; x++)
			sum = sum + rainfall[x];
		cout << "Total rainfall for all months: " << sum << " inches." << endl;
		cout << "Average rainfall for all months: " << sum / SIZE << endl << endl << endl;

		bubbleSort(rainfall, SIZE, month);
		cout << "The month with the lowest rainfall is: " << month[11] << " at " << rainfall[11] << " inches." << endl;
		cout << "The month with the highest rainfall is " << month[0] << " at " << rainfall[0] << " inches." << endl << endl << endl;

		cout << "The sorted months are as follows: " << endl;
		for(int i = 0; i < SIZE; i++)
			cout << setw(9) << right << month[i] << ": " << setw(4) << right << rainfall[i] << endl;
		system("pause");
}