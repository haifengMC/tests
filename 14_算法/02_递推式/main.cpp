#include<iostream>
#include<cmath>
using namespace std;
int f(double n)
{
	if (n == 1)
		return 1;
	else
		return 2 * f(n - 1) + pow(n, 3);
}
int main()
{
	double n;
	cin >> n;
	if (1 <= n < pow(10, 9))

	{
		cout << f(n) % 1000000007;
	}
	else
		cout << "error" << endl;

	return 0;
}