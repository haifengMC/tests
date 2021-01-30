#pragma once
#include <iostream>
using namespace std;

void f(const char* file = __FILE__, size_t n = __LINE__)
{
	cout << file << ":" << n << endl;
}

void f1()
{
	f();
}

void f2()
{
	f();
}

void f3()
{
	f();
}