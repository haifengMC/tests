#include <iostream>

using namespace std;

//void f(int i) { cout << "f " << i << endl; }
//
//
//class A
//{
//public:
//	int i = 10;
//	void f(int i) { cout << "A::f " << i << endl; }
//};
//
//int main()
//{
//	void* pF1 = f;
//	((void (*)(int))pF1)(1);
//
//
//	 void (A::*pF2)() = (void (A::*)())&A::f;
//	//pF = (void* A::*)&A::f;
//	//A a;
//	//(a.*pF)(1);
//
//	return 0;
//}
//基类

class D
{
public:
	D() { cout << "D()" << endl; }
	~D() { cout << "~D()" << endl; }
protected:
	int d;
};

class B :virtual public D
{
public:
	B() { cout << "B()" << endl; }
	~B() { cout << "~B()" << endl; }
protected:
	int b;
};

class A :virtual public D
{
public:
	A() { cout << "A()" << endl; }
	~A() { cout << "~A()" << endl; }
protected:
	int a;
};

class C :public B, public A
{
public:
	C() { cout << "C()" << endl; }
	~C() { cout << "~C()" << endl; }
protected:
	int c;
};

int main()
{
	cout << "Hello World!" << endl;
	C c;   //D, B, A ,C
	cout << sizeof(c) << endl;//16而不是24？
	cout << sizeof(C) << endl;
	cout << sizeof(B) << endl;
	cout << sizeof(A) << endl;
	cout << sizeof(D) << endl;
	return 0;
}
