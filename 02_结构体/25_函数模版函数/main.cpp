#include <iostream>
#include <functional>

using namespace std;

class A
{
	void f1() { cout << "f1()" << endl; }
	void f2() { cout << "f2()" << endl; }
	void f3() { cout << "f3()" << endl; }
	void f4() { cout << "f4()" << endl; }

public:
	template <typename T>
	void read(T func)
	{
		f1();
		func();
		f2();
	}
	template <typename T>
	void write(T func)
	{
		f3();
		func();
		f4();
	}
};

int main()
{
	int idx = 1;
	A a;
	a.read([&]() { cout << "read:" << idx << endl; });
	a.write([&]() { cout << "write:" << idx << endl; });

	return 0;
}