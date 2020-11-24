#include <iostream>
#include <vector>
#include <mutex>
#include <thread>

using namespace std;


int n = 0;
mutex m;

void f(int i)
{
	cout << n << endl;
	n = i;
	cout << n << endl;
}

int main()
{
	vector<thread> v;

	for (int i = 0; i < 100; ++i)
		v.emplace_back(f, i);

	for (auto& t : v)
		t.join();

	return 0;
}
