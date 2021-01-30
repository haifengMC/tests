#include <iostream>

using namespace std;

bool f1() { return true; }
bool f2() { return false; }

int main()
{
	cout << (10 + f1()) << endl;
	cout << (f1() + 10) << endl;
	cout << (10 + f2()) << endl;
	cout << (f2() + 10) << endl;


	int i = 20;
	i += f1();
	cout << i << endl;

	i += f2();
	cout << i << endl;

	return 0;
}