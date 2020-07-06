#include <vector>
#include <iostream>

using namespace std;

int main()
{
	vector<int> v = { 1,2,3 };
	for (vector<int>::const_iterator it = v.begin(); it != v.end(); ++it)
	{
		if (*it != v.back())
		{
			cout << *it << endl;
		}
	}


	return 0;
}