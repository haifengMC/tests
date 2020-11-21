#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector<bool> v1 = { false, false, false };
	vector<bool> v2 = { false, false };
	cout << (v1 == v2) << endl;


	return 0;
}