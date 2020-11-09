#pragma once

class A
{
public:
	int a = 10;
};

template <typename T>
class tA
{
public:
	T* t;
	tA(T* t) : t(t) {}
};