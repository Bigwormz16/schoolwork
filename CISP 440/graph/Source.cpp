/*		ISOMORPHIC GRAPHS
	Programmed by Ian Rosner
	CISP440 Douglass Spr2015
	5/9/2015

	Purpose: verify if two graphs are isomorphic,
	and, if so, display the bijection between the two.
	http://i.imgur.com/ND7Jksm.gif //problem statement

	Problem 1:
	  A B C D E F
	A 0 1 1 0 1 0
	B 1 0 1 0 0 1
	C 1 1 0 1 0 0
	D 0 0 1 0 1 1
	E 1 0 0 1 0 1
	F 0 1 0 1 1 0

	  1 2 3 4 5 6
	1 0 1 0 1 1 0
	2 1 0 1 0 0 1
	3 0 1 0 1 1 0
	4 1 0 1 0 0 1 
	5 1 0 1 0 0 1
	6 0 1 0 1 1 0

	
	Problem 2:
	  A B C D E
	A 0 1 0 1 0
	B 1 0 0 1 1
	C 0 1 0 1 1
	D 1 1 1 0 0
	E 0 1 1 0 0
	
	  1 2 3 4 5
	1 0 1 0 1 1
	2 1 0 0 1 0
	3 0 0 0 1 1
	4 1 1 1 0 1
	5 1 0 1 1 0			*/

#include <iostream>
#include <vector>
using namespace std;

//graph functions
void printVector(vector<vector<bool>> vec);
void permuteVector(vector<int> order, vector<vector<bool>> &vec, const vector<vector<bool>> graph);
bool isIsomorph(const vector<vector<bool>> original, const vector<vector<bool>> manip);

//permutation functions
unsigned int factorial(int num); //calculates factorial of k
void permuter(int n, vector<vector<int>> &perms); //wrapper function for permute
void permute(int perm[], int n, int r, int position, bool used[], vector<vector<int>> &perms);
int findNum(bool used[], int max); //permute helper function



int main(){
	// . . .
	//create matrixes

	//for each possible combination of matrix orientation,
		//compare each entry
			//if same, find bijection
	//if no bijection, not isomorphic

	//int count = 0; //bijection counter
	vector<vector<int>> permutations; //contains order permutations
	vector<vector<int>> bijections;

	static const char letters[] = {'A', 'B', 'C', 'D', 'E'};

	static const bool prob1_graph1[6][6] = {
		{ 0, 1, 1, 0, 1, 0 }, //A
		{ 1, 0, 1, 0, 0, 1 }, //B
		{ 1, 1, 0, 1, 0, 0 }, //C
		{ 0, 0, 1, 0, 1, 1 }, //D
		{ 1, 0, 0, 1, 0, 1 }, //E
		{ 0, 1, 0, 1, 1, 0 }  //F
	};

	static const bool prob1_graph2[6][6] = {
		{ 0, 1, 0, 1, 1, 0 }, //1
		{ 1, 0, 1, 0, 0, 1 }, //2
		{ 0, 1, 0, 1, 1, 0 }, //3
		{ 1, 0, 1, 0, 0, 1 }, //4
		{ 1, 0, 1, 0, 0, 1 }, //5
		{ 0, 1, 0, 1, 1, 0 }  //6
	};

	static const bool prob2_graph1[5][5] = {
		{ 0, 1, 0, 1, 0 }, //A
		{ 1, 0, 1, 1, 1 }, //B
		{ 0, 1, 0, 1, 1 }, //C
		{ 1, 1, 1, 0, 0 }, //D
		{ 0, 1, 1, 0, 0 }  //E
	};

	static const bool prob2_graph2[5][5] = {
		{ 0, 1, 0, 1, 1 }, //1
		{ 1, 0, 0, 1, 0 }, //2
		{ 0, 0, 0, 1, 1 }, //3
		{ 1, 1, 1, 0, 1 }, //4
		{ 1, 0, 1, 1, 0 }  //5
	};

	//input our graphs into vectors
	vector<vector<bool>> p1g1(6, vector<bool>(6));
	vector<vector<bool>> p1g2(6, vector<bool>(6));
	vector<vector<bool>> p2g1(5, vector<bool>(5));
	vector<vector<bool>> p2g2(5, vector<bool>(5));

	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 6; j++){
			p1g1[i][j] = prob1_graph1[i][j];
			p1g2[i][j] = prob1_graph2[i][j];
		}
	}

	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 5; j++){
			p2g1[i][j] = prob2_graph1[i][j];
			p2g2[i][j] = prob2_graph2[i][j];
		}
	}

	//our vector to be permuted on
	vector<vector<bool>> guineapig(6, vector<bool>(6));

	cout << "Problem 1:" << endl;

	permuter(6, permutations); //permutations now contains all possible orders

	if(bijections.size() == 0){
		cout << "No bijections found. Graphs are NOT isomorphic." << endl;
	} else {
		cout << bijections.size() << " bijections found. Graphs ARE isomorphic." << endl << endl;
		for(int i = 0; i < bijections.size(); i++){
			cout << "Bijection " << i + 1 << ":" << endl;
			for(int j = 0; j < bijections[i].size(); j++){
				cout << letters[bijections[i][j] - 1] << " -> " << (j + 1) << endl;
			}
			cout << endl;
		}
	}

	//setup for problem 2
	cout << endl << "Problem 2: " << endl;
	bijections.clear();

	guineapig.clear(); //resize our manip vector
	guineapig.resize(5);
	for(int i = 0; i < 5; i++){
		guineapig[i].resize(5);
	}
	
	permutations.clear();
	permuter(5, permutations);

	for(int i = 0; i < permutations.size(); i++){
		permuteVector(permutations[i], guineapig, p2g1);
		if(isIsomorph(p2g2, guineapig)){ //compare graph2 to permuted graph1
			//we have a match!
			bijections.push_back(permutations[i]);
		}
	}

	if(bijections.size() == 0){
		cout << "No bijections found. Graphs are NOT isomorphic." << endl;
	} else {
		cout << bijections.size() << " bijections found. Graphs ARE isomorphic." << endl << endl;
		for(int i = 0; i < bijections.size(); i++){
			cout << "Bijection " << i + 1 << ":" << endl;
			for(int j = 0; j < bijections[i].size(); j++){
				cout << letters[bijections[i][j] - 1] << " -> " << (j + 1) << endl;
			}
			cout << endl;
		}
	}
	
	system("pause");
	return 0;
}

void permuteVector(vector<int> order, vector<vector<bool>> &vec, const vector<vector<bool>> graph){
	//order contains a 'random' ordering - 5 3 2 1 4, for example
	//order[0] -> column 5 is now column 1

	for(int i = 0; i < graph.size(); i++){
		for(int j = 0; j < graph[i].size(); j++){
			vec[i][j] = graph[order[i] - 1][j];
		}
	} //rows  are now set

	//now we must rearrange the column order
	vector<vector<bool>> temp = vec;

	//NOT SURE IF WORKING
	for(int i = 0; i < graph.size(); i++){
		for(int j = 0; j < graph[i].size(); j++){
			//for each column, rearrange the order
			//temp contains the correct column arrangement
			vec[j][i] = temp[j][order[i] - 1];
		}
	}
}

bool isIsomorph(const vector<vector<bool>> original, const vector<vector<bool>> manip){
	//see if two graphs are isomorphic
	//if(original.size() != manip.size()) return false; //not same size

	for(int i = 0; i < original.size(); i++){
		for(int j = 0; j < original[i].size(); j++){
			if(manip[i][j] != original[i][j])
				return false;
		}
	}
	return true;
}

// permutation stuff
unsigned int factorial(int num){
	if (num == 0){
		return 1;
	} else {
		return num * factorial(num - 1);
	}
}

void permuter(int n, vector<vector<int>> &perms){
	//make array for permuter
	int d[10] = { 0 };
	bool used[10] = { false };

	//cout << (factorial(n)/factorial(n - k)) << " permutations total."
	//	 << endl << "Press ENTER key to print permutations." << endl;
	//fflush(stdin);
	//getchar();

	permute(d, n, n, 1, used, perms);
}

void permute(int perm[], int n, int r, int position, bool used[], vector<vector<int>> &perms){
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
				//crappy code incoming
				vector<int> tempvec;
				for(int p = 1; p < r; p++){
					tempvec.push_back(perm[p]);
				}
				tempvec.push_back(j);

				perms.push_back(tempvec);
			}
		}
		//cout << endl;
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
				permute(perm, n, r, position + 1, used, perms); //enter new permute thread

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

void printVector(vector<vector<bool>> vec){
	for(int i = 0; i < vec.size(); i++){
		for(int j = 0; j < vec[i].size(); j++){
			cout << vec[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}