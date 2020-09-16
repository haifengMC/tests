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

int main()
{
	map<int, A> m;
	A a(10);
	m.insert(make_pair(1, forward<A>(a)));
	ctor(m);

	return 0;
}