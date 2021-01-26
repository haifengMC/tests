#include <iostream>
#include <bitset>

using namespace std;

int main()
{
	char a = 1;
	char b = 2;
	char c = 3;
	char d = 4;
	uint32_t i = a << 24 | b << 16 | c << 8 | d;
	cout << i << "," << bitset<32>(i).to_string() <<endl;

	return 0;
}