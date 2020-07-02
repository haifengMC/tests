#pragma once

class A
{
	typedef bool(*IntFunc)(const int& i);
public:
	void funcInt(int i = 0, IntFunc f = (IntFunc)0);
	void funcDouble(double d = 0, bool(*f)(const double& d) = 0);
	template<typename T>
	void func(T t = T(), bool(*f)(const T & t) = 0);
};
