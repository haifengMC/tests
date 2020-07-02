#include <iostream>
#include "testImpl.h"

using namespace std;

int main()
{
	A a;
	a.funcInt();
	a.funcDouble();
	a.func<double>();
	a.func(10);

	return 0;
}