#include <iostream>
#include <string>

using namespace std;

int main()
{
	string s = "se1q:103";
	string seq = "seq:";
	cout << s.compare(0, seq.size(), seq) << endl;
	string sub = s.substr(seq.size());
	cout << sub << endl;
	char hello[] = "hello";
	string helloStr = hello;
	cout << sizeof(hello) << " " << helloStr.size() << endl;

	return 0;
}