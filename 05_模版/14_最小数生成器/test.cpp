#include "global.h"
#include "hSingleton.h"
#include "hTest.h"
#include "hTool.h"
#include "test.h"

using namespace std;

template<size_t N>
ostream& operator<<(ostream& os, const int(&key)[N])
{
	bool first = true;
	os << "{";
	for (const int& i : key)
	{
		if (first) first = false;
		else os << ",";

		os << i;
	}
	os << "}";

	return os;
}

template<typename Key, typename Val>
ostream& operator<<(ostream& os, const std::map<Key, Val>& m)
{
	bool first = true;
	os << "{";
	for (const pair<Key, Val>& p : m)
	{
		if (first) first = false;
		else os << ",";

		os << p.first << ":" << p.second;
	}
	os << "}";

	return os;
}

template<typename Key, typename Val, size_t N>
void insertKey(std::map<Key, Val>& m, const int(&key)[N], size_t limit)
{
	size_t cnt = 0;
	for (const int& i : key)
	{
		if (cnt++ >= limit)
			break;
		m.insert(make_pair(i, i * 10));
	}
	cout << m << endl;
}

template<typename Key, typename Val, size_t N>
void eraseKey(std::map<Key, Val>& m, const int(&key)[N])
{
	for (const int& i : key)
		m.erase(i);
	cout << m << endl;
}

TEST_INIT(Tst, testAll)

TEST(Tst, Tst1)
{
	map<int, int> m;
	NumGen<int, int> nGen(m, 100, 110);
	size_t cnt;
	int key1[6];
	cout << (cnt = nGen.getNum(key1)) << endl;
	cout << key1 << endl;
	insertKey(m, key1, cnt);
	int key2[] = { 101, 103, 104, 200 };
	cout << key2 << endl;
	eraseKey(m, key2);
	int key3[6];
	cout << (cnt = nGen.getNum(key3)) << endl;
	cout << key3 << endl;
	insertKey(m, key3, cnt);
	int key4[] = { 107, 108 };
	cout << key4 << endl;
	eraseKey(m, key4);
	int key5[6];
	cout << (cnt = nGen.getNum(key5)) << endl;
	cout << key5 << endl;
	insertKey(m, key5, cnt);
	int key6[6];
	cout << (cnt = nGen.getNum(key6)) << endl;
	cout << key6 << endl;
	insertKey(m, key6, cnt);
}

TEST(Tst, Tst2)
{
	map<int, int> m;
	NumGen<int, int> nGen(m, 100, 120);
	size_t cnt;
	int key1[10];
	cout << (cnt = nGen.getNum(key1)) << endl;
	cout << key1 << endl;
	insertKey(m, key1, cnt);
	int key2[] = { 101, 103, 104, 200 };
	cout << key2 << endl;
	eraseKey(m, key2);
	int key3[2];
	cout << (cnt = nGen.getNum(key3)) << endl;
	cout << key3 << endl;
	insertKey(m, key3, cnt);
	nGen.checkTimer();
	int key4[2];
	cout << (cnt = nGen.getNum(key4)) << endl;
	cout << key4 << endl;
	insertKey(m, key4, cnt);
	int key5[] = { 107, 108, 110, 111 };
	cout << key5 << endl;
	eraseKey(m, key5);
	int key6[6];
	cout << (cnt = nGen.getNum(key6)) << endl;
	cout << key6 << endl;
	insertKey(m, key6, cnt);
}