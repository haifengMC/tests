#include <iostream>
#include <typeinfo>

using namespace std;

class A {};


int main()
{
	int i;
	cout << typeid(i).name() << endl;

	A a;
	cout << typeid(a).name() << endl;

	return 0;
}
