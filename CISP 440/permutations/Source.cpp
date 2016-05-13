//display all permutations or combinations of a number
//programmed by ian rosner for douglass's CISP440
// spring 2015
#include <iostream>

using namespace std;

unsigned int factorial(int num); //calculates factorial of k
void permuter(int n, int k); //wrapper function for permute
void permute(int perm[], int n, int r, int position, bool used[]);
int findNum(bool used[], int max); //permute helper function
void combination(int n, int r); //combination module
bool repeat(); //prompt user to repeat

int main()
{
	short ans = 0;
	int n, k; //n choose k
	int rpt = true;


	while(rpt){
		ans = n = k = 0; //reset values

		while(ans > 2 || ans < 1){
			cout << " --- COMBINATIONS & PERMUTATIONS --- " << endl
				 << "Would you like to calculate permutations or combinations?" << endl
				 << "1 - Permutations (nPr)" << endl << "2 - Combinations (nCr)" << endl << "> ";
			cin.clear();
			cin >> ans;
		}

		//prompt user for n value
		while(n > 9 || n < 1){
			cout << endl << "Enter total items - n (1 to 9): ";
			cin.clear();
			cin >> n;
		}

		//prompt user for k value
		while(k > n || k < 1){
			cout << endl << "Enter total items - k (1 to " << n << "): ";
			cin.clear();
			cin >> k;
		}

		switch(ans){
		case 1: //do permute
			permuter(n, k);
			cout << endl << (factorial(n)/factorial(n - k)) << " permutations total." << endl;
			break;
		case 2: //do combinations
			cout << endl << (factorial(n) / (factorial(k)*(factorial(n - k)))) << " combinations total." << endl
				 << "Press ENTER key to print combinations." << endl;
			fflush(stdin);
			getchar();
			combination(n, k);
			cout << endl << (factorial(n) / (factorial(k)*(factorial(n - k)))) << " combinations total." << endl; //print before and after
			break;
		}

		system("pause");
		rpt = repeat();
		system("cls"); //clear screen
	}
}

bool repeat(){
	short rpt;
	cout << endl << "Would you like to run another calculation?" << endl
		 << "1 - Yes" << endl << "2 - No" << endl << "> ";
	cin >> rpt;

	if(rpt == 1)
		return true;

	return false;
}

unsigned int factorial(int num){
	if (num == 0){
		return 1;
	} else {
		return num * factorial(num - 1);
	}
}

void combination(int n, int r){ //algorithm taken from book
	int i, j = 0; //indices of combination elements
	int k; //for loop counter
	int max; //maximum allowable value for a digit
	int d[10]; //digits of combination (left to right)

	//create and write out smallest combination
	for (k = 1; k <= r; k++){
		d[k] = k;
	}

	for (int p = 1; p < r; p++){ //print combination
		cout << d[p] << ",";
	}
	cout << d[r] << '\t';

	//cout << endl << (factorial(n) / ((factorial(r)*(factorial(n - r)))));

	//create and write out remaining combinations
	for (k = 2; k <= (factorial(n) / ((factorial(r)*(factorial(n - r))))); k++){
		//look right to left for first non-max value
		max = n;
		i = r;
		while (d[i] == max){ //look left
			i = i - 1;
			max = max - 1;
		} //end while

		//now d[i] < max, need to increment d[i]

		d[i]++;
		
		//reset values right of d[i]

		for (j = i + 1; j <= r; j++){
			d[j] = d[j - 1] + 1;
		}

		for (int p = 1; p < r; p++){
			cout << d[p] << ',';
		}

		cout << d[r] << '\t';
	}
	cout << endl;
}

void permuter(int n, int k){
	//make array for permuter
	int d[10] = { 0 };
	bool used[10] = { false };

	cout << (factorial(n)/factorial(n - k)) << " permutations total."
		 << endl << "Press ENTER key to print permutations." << endl;
	fflush(stdin);
	getchar();

	permute(d, n, k, 1, used);
}


void permute(int perm[], int n, int r, int position, bool used[]){
/*inputs- perm[] is the current permutation string
		n is the maximum value for an 'object' to be
		r is the number of objects (perm[1] to perm[r])
		position is current r value
		used[] is ONLY used to print with, checks if number is available */

	//if position = r, we are at the end
	int newNum = 0;
	bool localUsed[10] = { false }; //for each n of current position
		//initialize localUsed to not use previous numbers
		for(int p = 1; p < position; p++){
			//cout << p << " is value " << perm[p] << endl; //debug
			localUsed[perm[p]] = true;
		}

	if(position == r){
		//print possibilities
		for(int j = 1; j <= n; j++){
			if(used[j] == false){
				for(int p = 1; p < r; p++){
					cout << perm[p] << ","; //fix formatting later
				}
				cout << j << '\t';
			}
		}
		cout << endl;
	} else { //carry on finding position possibilities
		for(int i = 1; i <= n; i++){ //try each number, 1 through n
			//find an open number (see if there even is one)
			newNum = findNum(localUsed, n);

			//debug
			if(newNum == -1){
				//cout << "in the current permutation, we have: "; //debug
				/*for(int dbg = 1; dbg <= position; dbg++){
					cout << perm[dbg] << ",";
				} */
				break; //no suitable numbers available ????
			}

				localUsed[newNum] = true; //this value will stay locked
				//cout << "choosing " << newNum << " as new num" << endl; //debug
				used[newNum] = true; //this value will be reset after returning from permute
			
				perm[position] = newNum; //set our permute value
				permute(perm, n, r, position + 1, used); //enter new permute thread

				/* return from permute thread -- need to free up last used number */
				used[newNum] = false;
		}
	}
}

int findNum(bool used[], int max){
	//cout << "finding new num" << endl << endl; //debug
	for(int k = 1; k <= max; k++){
		//cout << used[k] << " -- in use: " << k << endl; //debug
		if(used[k] == false){
			//cout << "found " << k << " available" << endl; //debug
			return k;
		}
	}
	//else, return 'break' code
	return -1;
}