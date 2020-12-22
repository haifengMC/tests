#include <iostream>
#include <bitset>

using namespace std;

int main()
{
	bitset<64> s;
	cout << s.count() << "/" << s.size() << endl;
	s.set(2);
	cout << s.to_string() << " " << s.count() << "/" << s.size() << endl;
	s.set(5);
	cout << s.to_string() << " " << s.count() << "/" << s.size() << endl;
	s.reset(2);
	cout << s.to_string() << " " << s.count() << "/" << s.size() << endl;
	return 0;
}