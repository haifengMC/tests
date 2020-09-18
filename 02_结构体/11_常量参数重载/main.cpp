#include <iostream>

using namespace std;

void func(int& i)
{
	cout << "int& i" << endl;
}

void func(int&& i)
{
	cout << "int&& i" << endl;
}

void func(const int& i)
{
	cout << "const int& i" << endl;
}

class A
{
public:
	void func(int& i)
	{
		cout << "int& i" << endl;
	}

	void func(int&& i)
	{
		cout << "int&& i" << endl;
	}

	void func(const int& i)
	{
		cout << "const int& i" << endl;
	}
};

class B
{
public:
	B() {}
	B(int& i) { cout << "int& i" << endl; }
	B(int&& i) { cout << "int&& i" << endl; }
	B(const int& i) { cout << "const int& i" << endl; }
};

int main()
{
	int i = 10;
	const int j = 10;

	func(i);
	func(j);
	func(move(i));

	cout << string(10, '-') << endl;

	A a;
	a.func(i);
	a.func(j);
	a.func(move(i));

	cout << string(10, '-') << endl;

	B b1(i);
	B b2(j);
	B b3(10);

	return 0;
}