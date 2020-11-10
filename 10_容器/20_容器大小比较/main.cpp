#include "global.h"
#include "hTool.h"

using namespace std;

hTool::Container ctor(cout);

struct Key
{
	vector<int> keys;

	Key() {}
	Key(initializer_list<int> il) : keys(il) {}

	bool operator<(const Key& k) const
	{
		int cntThis = keys.size();
		int cntK = k.keys.size();
		int cntMin = cntThis < cntK ? cntThis : cntK;

		for (int i = 0; i < cntMin; ++i)
		{
			if (keys[i] != k.keys[i])
				return keys[i] < k.keys[i];
		}

		if (cntThis != cntK)
			return cntThis < cntK;

		return false;
	}

	bool operator>(const Key& k) const
	{
		return k < *this;
	}
};

ostream& operator<<(ostream& os, const Key& k) { return ctor(k.keys); }

int main()
{
	Key k1 = { 1, 2, 3 };
	ctor(k1.keys);
	Key k2 = { 1, 2 };
	ctor(k2.keys);
	Key k3 = { 1, 2, 4 };
	ctor(k3.keys);
	Key k4 = { 1, 3 };
	ctor(k4.keys);

	cout << endl;
	cout << (k1 < k2) << " " << (k1 > k2) << endl;

	set<Key> kSet = { k4, k3, k1, k2 };
	ctor(kSet);

	return 0;
}