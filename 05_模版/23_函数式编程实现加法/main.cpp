#include "Function.h"
#include <iostream>
#include <vector>
#include <list>

using namespace std;

int main(int argc, char * argv[])
{
	int i = 0;
	vector<int> vi = {1, 1, 2, 3, 5, 8, 13};
	cout << sum(i, vi) << endl;
	i = 0;
	list<int> li = { 1, 1, 2, 3, 5, 8, 13 };
	cout << sum(i, li) << endl;

	float f = 0.0f;
	list<float> lf = { 1.1, 2.3, 5.8, 1.3 };
	cout << sum(f, lf) << endl;

	std::string s;
	std::vector<std::string> vs = {"k", "b", " hallo", " FP"};
	std::cout << concat(s, vs) << std::endl;
	s.clear();
	std::list<std::string> ls = { "k", "b", " hallo", " FP" };
	std::cout << concat(s, ls) << std::endl;

	return 0;
}
