#include <iostream>
#include <set>

using namespace std;

int main()
{
	set<int> a = { 1, 2, 3 };
	set<int> b;
	b.swap(a);


	return 0;
}