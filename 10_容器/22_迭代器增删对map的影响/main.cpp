#include <iostream>
#include <map>

using namespace std;



int main()
{
	map<int, int> m = { {1,1} };
	auto it = m.begin();
	m.erase(it);
	if (it == m.end())
		cout << "end" << endl;

	return 0;
}