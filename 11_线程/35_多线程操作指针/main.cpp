#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

using namespace std;
mutex coutM;
#define COUT_LOCK(x) { lock_guard<mutex> lk(coutM); cout << x << endl; }

struct A
{
	int a = 1;
	int b = 2;
	int c = 3;
};

struct B
{
	A* pA = new A;
	~B() { delete pA; }
};


void f1(int* i)
{
	COUT_LOCK(*i);
	++*i;
}

void f2(A* a)
{
	COUT_LOCK(a->a << " " << a->b << " " << a->c);
	++a->a;
	++a->b;
	++a->c;
}

void f3(B* b)
{
	COUT_LOCK(b->pA->a << " " << b->pA->b << " " << b->pA->c);
	++b->pA->a;
	++b->pA->b;
	++b->pA->c;
}

int main()
{

	{
		int i = 10;
		vector<thread> v;
		for (int j = 0; j < 9; ++j)
			v.emplace_back(f1, &i);

		for (auto& t : v)
			t.join();
	}
	cout << "--------------" << endl;
	{
		int* pi = new int(10);
		vector<thread> v;
		for (int j = 0; j < 9; ++j)
			v.emplace_back(f1, pi);

		for (auto& t : v)
			t.join();

		delete pi;
	}
	cout << "--------------" << endl;
	{
		A a;
		vector<thread> v;
		for (int j = 0; j < 9; ++j)
			v.emplace_back(f2, &a);

		for (auto& t : v)
			t.join();
	}
	cout << "--------------" << endl;
	{
		A* pA = new A;
		vector<thread> v;
		for (int j = 0; j < 9; ++j)
			v.emplace_back(f2, pA);

		for (auto& t : v)
			t.join();

		delete pA;
	}
	cout << "--------------" << endl;
	{
		B b;
		vector<thread> v;
		for (int j = 0; j < 9; ++j)
			v.emplace_back(f3, &b);

		for (auto& t : v)
			t.join();
	}
	cout << "--------------" << endl;
	{
		B* pB = new B;
		vector<thread> v;
		for (int j = 0; j < 9; ++j)
			v.emplace_back(f3, pB);

		for (auto& t : v)
			t.join();

		delete pB;
	}

	return 0;
}