#include <iostream>
#include <initializer_list>
#include <vector>

using namespace std;

int main()
{
	vector<int> v;
	v = { 1, 2, 3 };
	for (int i : v)
		cout << i << " ";
	cout << endl;
	//v += { 4,3,2 };
	v = { 4,3,2 };
	for (int i : v)
		cout << i << " ";
	cout << endl;

}