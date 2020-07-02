#pragma once
#include "test.h"

template<typename T>
void A::func(T t, bool(*f)(const T& t))
{
	if (f && f(t))
		std::cout << "ok" << std::endl;
	else
		std::cout << "err" << std::endl;
	std::cout << t << std::endl;
}