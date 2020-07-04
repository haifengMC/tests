#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class A
{
	bool operator()()
	{
		cout << "A" << endl;
		return true;
	}
};


int main()
{
	string s("1");
	istringstream is(s);
	char c;
	is.operator>>(c);
	cout << (int)c << endl;
	

	return 0;
}