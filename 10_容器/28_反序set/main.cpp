#include <iostream>
#include <set>

using namespace std;

int main()
{
	set<int, greater<int>> s;
	s.insert(1);
	s.insert(3);
	s.insert(5);

	for (auto i : s)
		cout << i << " ";
	cout << endl;

	{
		auto it = s.lower_bound(4);
		for (; it != s.end(); ++it)
			cout << *it << " ";
		cout << endl;
	}

	{
		auto it = s.lower_bound(3);
		for (; it != s.end(); ++it)
			cout << *it << " ";
		cout << endl;
	}

	{
		auto it = s.upper_bound(4);
		for (; it != s.end(); ++it)
			cout << *it << " ";
		cout << endl;
	}

	{
		auto it = s.upper_bound(3);
		for (; it != s.end(); ++it)
			cout << *it << " ";
		cout << endl;
	}

}