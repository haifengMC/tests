#include "global.h"
#include "hTool.h"
#include "hTest.h"

using namespace std;

#define CNT 100
hTool::Container cter(cout);
TEST_INIT(Tst, testAll)

struct A
{
public:
	int id = 0;
	map<int, A>& mapA;
	map<int, A>::iterator it;

	A(int id, map<int, A>& mapA) : id(id), mapA(mapA), it(mapA.end()) { cout << (it == mapA.end()) << endl; }
	A(const A& a) : id(a.id), mapA(a.mapA), it(a.it) {}

	void erase() { mapA.erase(it); }
};

ostream& operator<<(ostream& os, const A& a) { return os << a.id; }

map<int, A> mapA;
A* pA;

TEST(Tst, Tst1)
{
	for (int i = 0; i < CNT; ++i)
	{
		map<int, A>::iterator it = mapA.insert(make_pair(i, A(i, mapA))).first;
		it->second.it = it;

		if (i == 30)
			pA = &it->second;
	}
	cter(mapA);
}

TEST(Tst, Tst2)
{
	pA->erase();
}

TEST(Tst, Tst3)
{
	cter(mapA);
}

TEST(Tst, Tst4)
{
	mapA.erase(25);
}

TEST(Tst, Tst5)
{
	cter(mapA);
}


int main()
{
	testAll();
	return 0;
}