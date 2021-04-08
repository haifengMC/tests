#include <iostream>
#include <set>

using namespace std;

int main()
{
	set<int> s = { 1, 3, 4, 6 };
	auto it = std::prev(s.end());
	cout << *it << endl;

	return 0;
}