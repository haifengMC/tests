#include "global.h"
#include "hTool.h"

using namespace std;

hTool::Container ctor(cout);

class A
{
	int i = 0;
	friend ostream& operator<<(ostream& os, const A& a);
public:
	A(int i) : i(i) {}
	A(const A&) = delete;
	A(A&&) = default;
};

ostream& operator<<(ostream& os, const A& a) { return os << "A " << a.i; }
A* pA = (A*)malloc(sizeof(A));

int main()
{
	map<int, A> m;
	A a1(10);
	//m.insert(make_pair(1, forward<A>(a)));
	m.insert(make_pair(1, move(a1)));
	//m.emplace()
	//m[1] = move(a);
	ctor(m);

	vector<A> v;
	A a2(10);
	v.push_back(move(a2));
	ctor(v);

	list<A> l;
	A a3(10);
	l.push_back(move(a3));
	ctor(l);

	return 0;
}