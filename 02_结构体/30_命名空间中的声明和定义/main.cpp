#include <iostream>
#include "test.h"

using namespace std;

int main()
{
	ASpace::A a;
	cout << a.getName() << endl;
	ASpace::BSpace::B b;
	cout << b.getName() << endl;
	ASpace::CSpace::C c;
	cout << c.getName() << endl;

	return 0;
}