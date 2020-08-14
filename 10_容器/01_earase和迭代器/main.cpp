#include <iostream>
#include <list>
#include <vector>

using namespace std;

template<typename T>
ostream& operator<<(ostream& os, const list<T>& list)
{
	for (const T& t : list)
		os << t << " ";
	return os;
}

template<typename T>
ostream& operator<<(ostream& os, const vector<T>& list)
{
	for (const T& t : list)
		os << t << " ";
	return os;
}

int main()
{
	list<int> l1 = { 1, 2, 3, 4, 5 };
	cout << l1 << endl;
	for (auto it = l1.begin(); it != l1.end();)
	{
		if (2 == *it || 4 == *it)
			it = l1.erase(it);
		else
			++it;
	}
	cout << l1 << endl;

	vector<int> v = { 1, 2, 3, 4, 5 };
	cout << v << endl;
	for (auto it = v.begin(); it != v.end();)
	{
		if (2 == *it || 4 == *it)
			it = v.erase(it);
		else
			++it;
	}
	cout << v << endl;

	list<int> l2 = { 1, 2, 3, 4, 5 };
	cout << l2 << endl;
	for (auto it = l2.begin();
		it != l2.end();
		2 == *it || 3 == *it ? it = l2.erase(it) : ++it)
	{
		//do something
		if (4 == *it)
			*it = 3;
	}

	cout << l2 << endl;
}