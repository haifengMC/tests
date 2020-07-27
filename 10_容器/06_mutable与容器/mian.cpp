#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct A
{
	void pushBack() { v.push_back(10); }
private:
	mutable vector<int> v;
};

struct B
{
	map<int, A> m;
};


int main()
{
	A a;
	a.pushBack();
	B b;
	b.m.insert(make_pair(1, a));

	return 0;
}