#include <list>
#include <vector>
#include <iostream>

using namespace std;

void f(list<int>& l)
{
	for (auto i : l)
		cout << i << " ";
	cout << endl;
}

struct A
{
	list<int>::iterator _it;
	A(const list<int>::iterator& it) { _it = it; }
};
int main()
{
	{
		list<int> l1 = { 1, 2, 3 };
		list<int> l2 = { 4, 5, 6 };
		list<int> l3;

		auto it1 = l2.begin();
		auto it2 = it1;
		auto it3 = it1;
		++it2;
		cout << *it1 << " " << *it2 << endl;

		l1.splice(l1.begin(), l2, it1);
		cout << *it1 << endl;
		cout << *it3 << endl;
		cout << *++it1 << endl;
		cout << *++it3 << endl;
		cout << (it2 == l2.begin()) << endl;
		cout << *++it2 << endl;

		f(l1);
		f(l2);
		f(l3);
		//l1.splice(l1.begin(), l2, l2.end());
		l1.splice(l1.begin(), l3);
	}

	{
		list<int> l1;
		vector<A> v;
		v.emplace_back(l1.insert(l1.end(), 0));
		v.emplace_back(l1.insert(l1.end(), 1));
		v.emplace_back(l1.insert(l1.end(), 2));
		list<int> l2;
		for (auto& i : l1)
			l2.splice(l2.end(), l1, v[i]._it);
	}

	return 0;
}