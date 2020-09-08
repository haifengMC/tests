#include "global.h"
#include "hTool.h"

using namespace std;

hTool::Container ct(cout);

struct Data
{
	int i;
	list<Data>::iterator it;

	operator int() { return i; }
	operator int() const { return i; }
};

class DataList
{
public:
	list<Data> l;

	DataList& operator<<(int i)
	{
		auto it = l.insert(l.end(), {i});
		l.back().it = it;

		return *this;
	}

	void spliceBack(DataList& other, list<Data>::iterator it)
	{
		l.splice(l.begin(), other.l, it);
	}

	void spliceBack(DataList& other)
	{
		l.splice(l.begin(), other.l);
	}
};


int main()
{
	DataList l1, l2;
	l1 << 1 << 2 << 3;
	ct(l1.l);
	l2 << 4 << 5 << 6;
	ct(l2.l);
	cout << endl;

	auto itOld1 = l1.l.begin();
	l1.spliceBack(l2, l2.l.begin());
	ct(l1.l);
	ct(l2.l);
	cout << endl;
	for (auto it = l1.l.begin(); it != itOld1; ++it)
		cout << *it << " ";
	cout << endl;

	auto itOld2 = l2.l.begin();
	l2.spliceBack(l1);
	ct(l1.l);
	ct(l2.l);
	cout << endl;
	for (auto it = l2.l.begin(); it != itOld2; ++it)
		cout << *it << " ";


	return 0;
}