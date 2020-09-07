#include "global.h"
#include "hTest.h"
#include "hTool.h"

using namespace std;

//hTool::Container ctor(cout);

TEST_INIT(Tst, testAll)

class UniqueTst : public hTool::hUniqueMapVal<size_t, UniqueTst>
{
	size_t id = 0;
public:
	UniqueTst() : hTool::hUniqueMapVal<size_t, UniqueTst>(id, this) {}
	UniqueTst(size_t i) : hTool::hUniqueMapVal<size_t, UniqueTst>(id, this) { id = i; }
	UniqueTst(const UniqueTst& t) : hTool::hUniqueMapVal<size_t, UniqueTst>(id, this) { id = t; }
};

TEST(Tst, Tst1)
{
	map<size_t, UniqueTst> m;
	hTool::hUniqueIdGen<size_t, UniqueTst> gen(m, 10);
	gen.resize(100, 500);
	UniqueTst t1;
	gen.insert(t1);
	
	cout << gen << endl;
}

TEST(Tst, Tst2)
{
	UniqueTst t1(10), t2(20);
	cout << t1 << ", " << t2 << endl;
	UniqueTst t3 = t2;
	cout << t2 << ", " << t3 << endl;
	t2(200);
	cout << t2 << ", " << t3 << endl;
	t3(300);
	cout << t1 << "," << t2 << ", " << t3 << endl;

	map<size_t, UniqueTst> m;
	hTool::hUniqueIdGen<size_t, UniqueTst> gen(m, 10);
	gen.resize(100, 500);
	gen << t1 << t2 << t3;
	cout << gen << endl;

}

TEST(Tst, Tst3)
{
	map<size_t, UniqueTst> m;
	hTool::hUniqueIdGen<size_t, UniqueTst> gen(m, 10);
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
	UniqueTst t1(10);
	cout << t1 << endl;
	gen << t1;
	cout << gen << " " << t1 << endl;
	gen.erase(t1);
	cout << gen << " " << t1 << endl;
}

int main()
{
	testAll();

	return 0;
}