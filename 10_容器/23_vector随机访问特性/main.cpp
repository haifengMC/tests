#include <iostream>
#include <vector>

using namespace std;



int main()
{
	vector<int> v;
	cout << v.capacity() << " " << v.size() << endl;
	v.reserve(10);
	cout << v.capacity() << " " << v.size() << endl;
	v.resize(20);
	cout << v.capacity() << " " << v.size() << endl;
	cout << v[2] << endl;

	return 0;
}
