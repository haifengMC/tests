#include <iostream>

using namespace std;

class A
{
public:
	void operator()()
	{
		cout << "empty" << endl;
	}

	template <class T, class ... Args>
	void operator()(T first, Args ... last)
	{
		cout << "parameter " << first << endl;
		this->operator()(last...);
	}
}; 

class B
{
public:
	template <class Func, class ... Args>
	void operator()(Func func, Args ... args)
	{
		func(args...);
	}
};

void add(int a, int b) { cout << (a + b) << endl; }
void testPrint(string s, int i) { cout << s << i << endl; }

int main()
{
	A a;
	a(1, 2, 3);

	cout << endl;
	B b;
	b(add, 1, 2);
	b(testPrint, "hello", 2);

	return 0;
}