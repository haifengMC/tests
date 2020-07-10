#include <iostream>
#include <map>

using namespace std;

int main()
{
	map<int, int> m;
	auto less = m.key_comp();
	cout << less(3, 5) << endl;

	return 0;
}