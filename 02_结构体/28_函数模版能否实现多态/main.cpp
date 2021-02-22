#include <iostream>
#include <stdarg.h>

using namespace std;

void f(int i) { int a; cout << &f << " " << &i << " " << &a << endl; }

struct A 
{
	virtual void func(...) { cout << "A" << endl; }
	void f(int i) { int a; cout << &A::f << " " << &i << " " << &a << endl; }
	virtual ~A() {}
};

struct B : public A
{
	void f(int i) { int a; cout << &B::f << " " << &i << " " << &a << endl; }
	void func(...)
	{
		cout << "B" << endl;
		//va_list pArgs;
		//va_start(pArgs, );
		//s = va_arg(pArgs, decltype(s));
		//va_end(pArgs);
		//cout << a << " " << b << endl;
	}
};

struct C : public A
{
	void f(int i) { int a; cout << &C::f << " " << &i << " " << &a << endl; }
	void func(...)
	{
		cout << "C" << endl; 
		//va_list pArgs;
		//va_start(pArgs, sizeof(void*));
		//s = va_arg(pArgs, decltype(s));
		//va_end(pArgs);
		//cout << s << endl;
	}
};

int main()
{
	f(1);
	A* pB = new B;
	A* pC = new C;

	//pB->func(1, 2);
	//pC->func("hello");
	pB->f(1);
	pC->f(1);
	delete pB;
	delete pC;
}