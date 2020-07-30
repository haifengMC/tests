#include "global.h"
#include "hTool.h"

using namespace std;

class TestMapVal : public hTool::UniqueMapVal<>
{
	unsigned int id;
public:
	TestMapVal(const unsigned int& i) : UniqueMapVal<>(id)
	{
		id = i;
	}
	TestMapVal(const TestMapVal& v) : UniqueMapVal<>(id)
	{
		id = v.id;
	}

	friend ostream& operator<<(ostream& os, const TestMapVal& val);
};
ostream& operator<<(ostream& os, const TestMapVal& val)
{
	return os << "[" << val.id << " r" << val.idRef << "]";
}

int main()
{
	TestMapVal t1(10), t2(20);
	cout << t1 << ", " << t2 << endl;
	TestMapVal t3 = t2;
	cout << t2 << ", " << t3 << endl;
	t2.setIndex(200);
	cout << t2 << ", " << t3 << endl;
	t3.setIndex(300);
	cout << t2 << ", " << t3 << endl;

	map<unsigned int, TestMapVal> m;
	hTool::UniqueIdGen<unsigned int, TestMapVal> gen(m);
	cout << gen << endl;
	gen.insert(TestMapVal(3));
	cout << gen << endl;
	gen.insert(TestMapVal(1));
	cout << gen << endl;
	gen.insert(TestMapVal(gen.getInvaild()));
	cout << gen << endl;
	gen.genCheck();
	cout << gen << endl;
	gen.resize(1, 5);
	cout << gen << endl;
	gen.insert(TestMapVal(gen.getInvaild()));
	cout << gen << endl;
	gen.insert(TestMapVal(gen.getInvaild()));
	cout << gen << endl;
	gen.resize(2, 4);
	cout << gen << endl;
	gen.resize(1, 10);
	cout << gen << endl;
	gen.insert(TestMapVal(gen.getInvaild()));
	cout << gen << endl;
	gen.insert(TestMapVal(gen.getInvaild()));
	cout << gen << endl;
	gen.insert(TestMapVal(gen.getInvaild()));
	cout << gen << endl;
	gen.insert(TestMapVal(gen.getInvaild()));
	cout << gen << endl;
	gen.insert(TestMapVal(gen.getInvaild()));
	cout << gen << endl;
	gen.insert(TestMapVal(gen.getInvaild()));
	cout << gen << endl;
	gen.insert(TestMapVal(gen.getInvaild()));
	cout << gen << endl;
	gen.insert(TestMapVal(gen.getInvaild()));
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

	return 0;
}