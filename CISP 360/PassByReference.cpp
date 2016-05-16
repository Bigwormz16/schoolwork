#include <iostream>
using namespace std;

int doSomething(int *x, int *y)
{
	int temp = *x;
	*x = *y * 10;
	*y = temp * 10;
	return *x + *y;
}

int main(void)
{
	int something = 0,
		x = 3,
		y = 6;

	cout << "---Initial Values---" << endl;
	cout << "X: " << x << endl;
	cout << "Y: " << y << endl;
	cout << "Something: " << something << endl << endl;

	something = doSomething(&x, &y);

	cout << "---Returned Values---" << endl;
	cout << "X: " << x << endl;
	cout << "Y: " << y << endl;
	cout << "Something: " << something  << " (X + Y)" << endl << endl;

	system("pause");
}