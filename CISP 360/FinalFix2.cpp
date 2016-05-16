/* Ian Rosner
   Fix Program 2
*/
#include <iostream>
#include <iomanip> // setprecision, setw, etc
#define MAX_STUDENTS 5 // set higher to 2 for testing purposes
using namespace std;

int getStudentCount();
void getExamScores(int numStudents, int examScore[]); // missing prototype added
void getLabScores(int numStudents, double labScore[]);
void calculatePointGrades(int numStudents, const int examScore[], const double labScore[], double pointGrade[]);
void calculateLetterGrades(int numStudents, const double pointGrade[], char letterGrade[]);
void showGradeData(int numStudents, const int examScore[], const double labScore[], const double pointGrade[], const char letterGrade[]);

// ^ moved out of main to global scope and fixed parameters to match declaration

int main(void)
{
	int numStudents = getStudentCount(); // tidy up declaration
	int examScore[MAX_STUDENTS]; // turned vars into arrays with size of MAX_STUDENTS
	double labScore[MAX_STUDENTS]; 
	double pointGrade[MAX_STUDENTS]; 
	char letterGrade[MAX_STUDENTS]; 


	getExamScores(numStudents, examScore);
	getLabScores(numStudents, labScore);
	calculatePointGrades(numStudents, examScore, labScore, pointGrade);
	calculateLetterGrades(numStudents, pointGrade, letterGrade);
	showGradeData(numStudents, examScore, labScore, pointGrade, letterGrade);

	cin.ignore(2);
}



int getStudentCount()
{
	int count = 0;
	cout << "Number of students in class:  ";
	cin >> count;
	return count;
}

void getExamScores(int numStudents, int examScore[])
{
	for(int i=0; i < numStudents; i++) // <= to <
	{
		cout << "Enter exam score for student " << i+1 << ":  "; // removed space before :
		cin >> examScore[i]; //added [i]
	}
}

void getLabScores(int numStudents, double labScore[])
{
	for(int i=0; i < numStudents; i++)
	{
		cout << "Enter lab score for student " << i+1 << ":  ";
		cin >> labScore[i];
	}
}

void calculatePointGrades(int numStudents, const int examScore[], const double labScore[], double pointGrade[])
{
	for (int i=0; i < numStudents; i++) pointGrade[i] = .3 * examScore[i] + .7 * labScore[i];
}

void calculateLetterGrades(int numStudents, const double pointGrade[], char letterGrade[])
{
	for (int i=0; i<numStudents; i++)
	{ // assuming these values are correct (A is usually 90% and whatnot), left unchanged
		letterGrade[i] = 'F';
		if(pointGrade[i] >= 50.0)
			letterGrade[i] = 'D';
		if(pointGrade[i] >= 60.0)
			letterGrade[i] = 'C';
		if(pointGrade[i] >= 70.0)
			letterGrade[i] = 'B';
		if(pointGrade[i] >= 80.0)
			letterGrade[i] = 'A';
	}
}

void showGradeData(int numStudents, const int examScore[], const double labScore[], const double pointGrade[], const char letterGrade[])
{
	int intArrayAve(int numStudents, const int examScore[]); // submodule prototypes corrected
	double doubleArrayAve(int numStudents, const double labScore[]);

	cout << setprecision(1) << fixed;
	cout << endl << endl;
	cout << "SN     " << "Exam     " << "Lab      " << "Point   "  << "Letter" << endl;
	cout << "       " << "         " << "Ave.     " << "Grade   "  << "Grade " << endl;
	cout << "______________________________________" << endl << endl ;

	for(int i=0; i < numStudents; i++)
	{
		cout << setw(3) << i+1 << "   " << setw(5) << examScore[i] << "   " << setw(6) << labScore[i] << "      " << setw(5) << pointGrade[i] << "    " << setw(1) << letterGrade[i] << endl;
	}

	cout << endl << endl << "Exam Average:  \t\t" << intArrayAve(numStudents, examScore) << endl;
	cout << "Lab Ave. Average:  \t" << doubleArrayAve(numStudents, labScore) << endl;
	cout << "Point Grade Average:  \t" << doubleArrayAve(numStudents, pointGrade) << endl << endl;
}

int intArrayAve(int numStudents, const int examScore[])
{
	int sum = 0;
	for (int i=0; i < numStudents; i++) sum += examScore[i]; // += instead of *=
	return sum/numStudents; // return line
}

double doubleArrayAve(int numStudents, const double labScore[])
{
	double sum = 0.0;
	for (int i=0; i < numStudents; i++) sum += labScore[i]; // *= to +=
	return sum/numStudents; // divided by instead of *
}