#include <iostream>

using namespace std;

struct A
{
	int a;
	int* b;
};


int main()
{
	A a = { 1 };
	cout << a.a << " " << a.b << endl;


	return 0;
}