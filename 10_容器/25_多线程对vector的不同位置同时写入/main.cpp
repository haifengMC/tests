#include <iostream>
#include <vector>
#include <thread>

using namespace std;

void f(vector<int>* v, int i)
{
	v->at(i) = i;
}

int main()
{
	vector<thread> thrds;

	size_t n = 100;
	vector<int> v(n, 0);

	for (auto i : v)
		cout << i << " ";
	cout << endl;

	for (size_t i = 0; i < n; ++i)
		thrds.emplace_back(f, &v, i);

	for (auto i : v)
		cout << i << " ";
	cout << endl;

	for (auto& t : thrds)
		t.join();

	return 0;
}