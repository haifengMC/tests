#include <iostream>
#include <set>

using namespace std;

void f1(std::set<int>& s)
{
	int i = 0;
	for (auto it = s.begin(); it != s.end(); it = s.upper_bound(i))
		cout << (i = *it) << " ";

	cout << endl;
}

void f2(std::set<int>& s)
{
	int i = 0;
	for (auto it = s.begin(); it != s.end(); it = s.lower_bound(i + 1))
		cout << (i = *it) << " ";

	cout << endl;
}

int main()
{
	std::set<int> s1 = { 1, 3, 5, 6, 8 };
	f1(s1);
	f2(s1);
	std::set<int> s2 = { 0, 2, 4, 5, 7 };
	f1(s2);
	f2(s2);


	return 0;
}