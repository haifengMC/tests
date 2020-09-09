#include <list>
#include <iostream>

using namespace std;

int main()
{
	list<int> l1 = { 1, 2, 3 };
	list<int> l2 = { 4, 5, 6 };

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

	l1.splice(l1.begin(), l2, l2.end());

	return 0;
}