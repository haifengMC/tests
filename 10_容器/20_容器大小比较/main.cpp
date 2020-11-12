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

	//bool operator==(const Key& k) const
	//{
	//	if (keys.size() != k.keys.size())
	//		return false;
	//
	//	return !memcmp(keys.data(), k.keys.data(), keys.size() * sizeof(Key));
	//}
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
	Key k5 = { 1, 4 };
	ctor(k5.keys);
	Key k6 = { 1 };
	ctor(k6.keys);

	cout << endl;
	cout << (k1 < k2) << " " << (k1 > k2) << endl;

	set<Key> kSet = { k5, k4, k3, k1, k2, k6 };
	ctor(kSet);

	cout << endl;
	auto pair1 = kSet.equal_range(k2);
	for (auto it = pair1.first; it != pair1.second; ++it)
		cout << *it << endl;

	cout << "----" << endl;

	auto beg1 = kSet.find(k2);
	auto end1 = kSet.find(k4);
	for (auto it = beg1; it != end1; ++it)
		cout << *it << endl;

	cout << "----" << endl;
	
	//cout << (k1 == k2) << (k2 == k2) << endl;

	cout << "----" << endl;
	for (auto it = beg1; it != kSet.end() && it != end1;)
		kSet.erase(it++);
	ctor(kSet);
	cout << "----" << endl;
	kSet.insert(k1);
	kSet.insert(k3);
	ctor(kSet) << endl;
	auto beg2 = kSet.lower_bound(k2);
	auto end2_1 = kSet.lower_bound(k4);
	auto end2_2 = kSet.upper_bound(k4);
	cout << *end2_1 << " " << *end2_2 << endl;
	for (auto it = beg2; it != end2_1; ++it)
		cout << *it << " ";
	cout << endl;
	for (auto it = beg2; it != end2_2; ++it)
		cout << *it << " ";


	return 0;
}