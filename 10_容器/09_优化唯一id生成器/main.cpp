#include "global.h"
#include "hTest.h"
#include "hTool.h"

using namespace std;

//hTool::Container ctor(cout);

TEST_INIT(Tst, testAll)

class UniqueTst1 : public hTool::hUniqueMapVal<size_t, UniqueTst1>
{
	size_t id = 0;
public:
	UniqueTst1() : hTool::hUniqueMapVal<size_t, UniqueTst1>(id, this) {}
	UniqueTst1(size_t i) : hTool::hUniqueMapVal<size_t, UniqueTst1>(id, this) { id = i; }
	UniqueTst1(const UniqueTst1& t) : hTool::hUniqueMapVal<size_t, UniqueTst1>(id, this) { id = t; }
};

class UniqueTst2 : public hTool::hUniqueMapVal<size_t, UniqueTst2>
{
	size_t id = 0;
public:
	UniqueTst2() : hTool::hUniqueMapVal<size_t, UniqueTst2>(id, this) {}
	UniqueTst2(size_t i) : hTool::hUniqueMapVal<size_t, UniqueTst2>(id, this) { id = i; }
	UniqueTst2(const UniqueTst2&& t) : hTool::hUniqueMapVal<size_t, UniqueTst2>(id, this) { id = t.id; }
};

struct A { string s; A(const string& s) : s(s) {} };
struct B { string s; B(const string& s) : s(s) {} };
class UniqueTst3 : public hTool::hUniqueMapVal<size_t, UniqueTst3>
{
	size_t id = 0;
	hTool::hAutoPtr<A> pA;
	hTool::hAutoPtr<B> pB;
public:
	UniqueTst3() : hTool::hUniqueMapVal<size_t, UniqueTst3>(id, this)
	{
		pA.emplace("abc");
		pB.emplace("def");
	}
	UniqueTst3(size_t i) : hTool::hUniqueMapVal<size_t, UniqueTst3>(id, this) { id = i; }
	UniqueTst3(UniqueTst3&& t) noexcept : hTool::hUniqueMapVal<size_t, UniqueTst3>(id, this)
	{
		cout << "move" << endl;
		id = t.id;
		pA = move(t.pA);
		pB = move(t.pB);
	}
};

TEST(Tst, Tst1)
{
	map<size_t, UniqueTst1> m;
	hTool::hUniqueIdGen<size_t, UniqueTst1> gen(m, 10);
	gen.resize(100, 500);
	UniqueTst1 t1;
	gen.insert(t1);
	
	cout << gen << endl;
}

TEST(Tst, Tst2)
{
	UniqueTst1 t1(10), t2(20);
	cout << t1 << ", " << t2 << endl;
	UniqueTst1 t3 = t2;
	cout << t2 << ", " << t3 << endl;
	t2(200);
	cout << t2 << ", " << t3 << endl;
	t3(300);
	cout << t1 << "," << t2 << ", " << t3 << endl;

	map<size_t, UniqueTst1> m;
	hTool::hUniqueIdGen<size_t, UniqueTst1> gen(m, 10);
	gen.resize(100, 500);
	gen << t1 << t2 << t3;
	cout << gen << endl;

}

TEST(Tst, Tst3)
{
	map<size_t, UniqueTst1> m;
	hTool::hUniqueIdGen<size_t, UniqueTst1> gen(m, 10);
	cout << gen << endl;
	gen << 3;
	cout << gen << " " << gen.back()->first << endl;
	gen << 1;
	cout << gen << " " << gen.back()->first << endl;
	gen << gen.getInvaild();
	cout << gen << endl;
	gen.genCheck();
	cout << gen << endl;
	gen.resize(1, 5);
	cout << gen << endl;
	gen << gen.getInvaild();
	cout << gen << endl;
	gen << gen.getInvaild();
	cout << gen << endl;
	gen << gen.getInvaild();
	cout << gen << endl;
	gen.resize(2, 4);
	cout << gen << endl;
	gen.resize(1, 10);
	cout << gen << endl;
	gen << gen.getInvaild();
	cout << gen << endl;
	gen << gen.getInvaild();
	cout << gen << endl;
	gen << gen.getInvaild();
	cout << gen << endl;
	gen << gen.getInvaild();
	cout << gen << endl;
	gen << gen.getInvaild();
	cout << gen << endl;
	gen << gen.getInvaild();
	cout << gen << endl;
	gen << gen.getInvaild();
	cout << gen << endl;
	gen << gen.getInvaild();
	cout << gen << endl;
	gen.resize(2, 8);
	cout << gen << endl;
	gen.putKey(2);
	gen.putKey(3);
	gen.putKey(5);
	gen.putKey(7);
	cout << gen << endl;
	gen.resize(3, 7);
	cout << gen << endl;
	UniqueTst1 t1(10);
	cout << t1 << endl;
	gen << t1;
	cout << gen << " " << t1 << endl;
	gen.erase(t1);
	cout << gen << " " << t1 << endl;
}

TEST(Tst, Tst4)
{
	map<size_t, UniqueTst2> m;
	hTool::hUniqueIdGen<size_t, UniqueTst2> gen(m, 10);
	gen.resize(100, 500);
	UniqueTst2 t1;
	gen.insert(move(t1));
	gen << move(t1);

	cout << gen << endl;
}

TEST(Tst, Tst5)
{
	map<size_t, UniqueTst2> m;
	hTool::hUniqueIdGen<size_t, UniqueTst2> gen(m, 10);
	cout << gen << endl;
	gen << 3;
	cout << gen << " " << gen.back()->first << endl;
	gen << 1;
	cout << gen << " " << gen.back()->first << endl;
	gen << gen.getInvaild();
	cout << gen << endl;
	gen.genCheck();
	cout << gen << endl;
	gen.resize(1, 5);
	cout << gen << endl;
	gen << gen.getInvaild();
	cout << gen << endl;
	gen << gen.getInvaild();
	cout << gen << endl;
	gen << gen.getInvaild();
	cout << gen << endl;
	gen.resize(2, 4);
	cout << gen << endl;
	gen.resize(1, 10);
	cout << gen << endl;
	gen << gen.getInvaild();
	cout << gen << endl;
	gen << gen.getInvaild();
	cout << gen << endl;
	gen << gen.getInvaild();
	cout << gen << endl;
	gen << gen.getInvaild();
	cout << gen << endl;
	gen << gen.getInvaild();
	cout << gen << endl;
	gen << gen.getInvaild();
	cout << gen << endl;
	gen << gen.getInvaild();
	cout << gen << endl;
	gen << gen.getInvaild();
	cout << gen << endl;
	gen.resize(2, 8);
	cout << gen << endl;
	gen.putKey(2);
	gen.putKey(3);
	gen.putKey(5);
	gen.putKey(7);
	cout << gen << endl;
	gen.resize(3, 7);
	cout << gen << endl;
	UniqueTst2 t1(10);
	cout << t1 << endl;
	gen << t1;
	cout << gen << " " << t1 << endl;
	gen.erase(t1);
	cout << gen << " " << t1 << endl;
}

TEST(Tst, Tst6)
{
	map<size_t, UniqueTst3> m;
	hTool::hUniqueIdGen<size_t, UniqueTst3> gen(m, 10);
	gen.resize(100, 500);
	UniqueTst3 t1;
	gen.insert(t1);

	cout << gen << endl;
}

int main()
{
	testAll();

	return 0;
}