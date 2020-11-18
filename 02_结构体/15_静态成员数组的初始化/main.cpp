#include <iostream>

using namespace std;

struct A
{
	static int arr[2];
};
int A::arr[2];

int main()
{
	for (int i : A::arr)
		cout << i << " ";


	return 0;
}