#include <iostream>
#include <map>

using namespace std;

void f(int i)
{
	cout << (i ? i > 0 ? 0 : 1 : 2) << endl;
}

int main()
{
	multimap<int, int> m;
	m.insert(make_pair(1, 1));
	m.insert(make_pair(1, 2));
	m.insert(make_pair(1, 3));
	m.insert(make_pair(2, 3));
	m.insert(make_pair(2, 2));
	m.insert(make_pair(2, 1));
	m.insert(make_pair(3, 4));
	m.insert(make_pair(3, 4));
	m.insert(make_pair(3, 4));

	for (auto& p : m)
		cout << "{" << p.first << "," << p.second << "}";
	cout << endl;

	auto it = m.find(2);
	for (auto i = it; i != m.end(); ++i)
		cout << "{" << i->first << "," << i->second << "}";
	cout << endl;

	auto range = m.equal_range(2);
	for (;range.first != range.second; ++range.first)
		cout << "{" << range.first->first << "," << range.first->second << "}";
	cout << endl;

	range = m.equal_range(2);

	f(0);
	f(-1);
	f(1);

	return 0;
}