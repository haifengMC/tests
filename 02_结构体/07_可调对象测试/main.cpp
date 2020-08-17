#include <map>
#include <string>
#include <functional>
#include <iostream>

using namespace std;

map<string, function<int(int, int)>> funMap;

int add(int a, int b) { return a + b; }

class Mul
{
	int operator()(int a, int b) const { return a * b; }
};

int mul(int a, int b) { return a * b; }

int main()
{
	funMap["add"] = add;
	funMap["sub"] = [](int a, int b) {return a - b; };
	//Mul mul;
	int (*pMul)(int, int) = mul;
	funMap["mul"] = mul;

	cout << funMap["add"](10, 20) << endl;
	cout << funMap["sub"](10, 20) << endl;
	cout << funMap["mul"](10, 20) << endl;

	return 0;
}