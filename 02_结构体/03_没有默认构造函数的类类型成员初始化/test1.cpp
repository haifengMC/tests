#include <iostream>
#include <string>
#include "test2.h"
#include "test1.h"

#define VA_B reinterpret_cast<B*>(b)

A::A(int i) : b(new B(i)) {}
A::~A() { delete b; }
void A::printB()
{
	VA_B->printB();
}
void A::printS()
{
	std::cout << s << std::endl;
}