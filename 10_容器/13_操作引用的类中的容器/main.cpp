#include <iostream>
#include <set>

using namespace std;

class A;
struct B
{
	B(A& a) : a(a) {}

	void func1(int i);

	A& a;
};

class A
{
	friend struct B;
	set<int> s;
};

void B::func1(int i) { cout << a.s.erase(i) << endl; }

int main()
{
	A a;
	B b(a);
	b.func1(1);

	return 0;
}