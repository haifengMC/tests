#include <iostream>
#include <vector>

using namespace std;

struct A
{
	A(int i) : i(i) {}
	int i;
};

void p(const vector<A>& vA)
{
	for (auto& a : vA)
		cout << a.i << " ";
	cout << endl;
}

int main()
{
	vector<int> v;
	cout << v.capacity() << " " << v.size() << endl;
	v.reserve(10);
	cout << v.capacity() << " " << v.size() << endl;
	v.resize(20);
	cout << v.capacity() << " " << v.size() << endl;
	cout << v[2] << endl;

	vector<A> vA = { 1,2,3 };
	cout << vA.capacity() << " " << vA.size() << endl;
	p(vA);
	vA.resize(10, 20);
	cout << vA.capacity() << " " << vA.size() << endl;
	p(vA);


	return 0;
}
