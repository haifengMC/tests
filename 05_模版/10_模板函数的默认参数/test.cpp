#include "test.h"
#include <iostream>

void A::funcInt(int i, IntFunc f)
{
	if (f && f(i))
		std::cout << "ok" << std::endl;
	else
		std::cout << "fail" << std::endl;
	std::cout << i << std::endl;

}

void A::funcDouble(double d, bool(*f)(const double& d))
{
	if (f && f(d))
		std::cout << "ok" << std::endl;
	else
		std::cout << "fail" << std::endl;
	std::cout << d << std::endl;
}
