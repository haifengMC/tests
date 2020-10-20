#include <set>
#include <iostream>

using namespace std;

int main()
{
	set<pair<int, int>> s;

	s.insert(make_pair(1, 2));
	s.insert(make_pair(2, 1));
	s.insert(make_pair(1, 2));

	cout << (s.find(make_pair(2, 1)) != s.end()) << endl;

	return 0;
}