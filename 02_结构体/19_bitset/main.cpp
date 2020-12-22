#include <iostream>
#include <bitset>

using namespace std;

uint8_t calcBit(uint64_t n, uint8_t i = 1)
{
	if (n / 2)
		return calcBit(n / 2, i + 1);

	if (n) 
		return i;
	
	if (i) 
		return i - 1;

	return i;
}

int main()
{
	bitset<10> s;
	cout << s.count() << "/" << s.size() << "/" << (uint16_t)calcBit(s.to_ulong()) << endl;
	s.set(2);
	cout << s.to_string() << " " << s.count() << "/" << s.size() << "/" << (uint16_t)calcBit(s.to_ulong()) << endl;
	s.set(5);
	cout << s.to_string() << " " << s.count() << "/" << s.size() << "/" << (uint16_t)calcBit(s.to_ulong()) << endl;
	s.reset(2);
	cout << s.to_string() << " " << s.count() << "/" << s.size() << "/" << (uint16_t)calcBit(s.to_ulong()) << endl;
	s.reset();
	cout << s.to_string() << " " << s.count() << "/" << s.size() << "/" << (uint16_t)calcBit(s.to_ulong()) << endl;
	s.set(0);
	cout << s.to_string() << " " << s.count() << "/" << s.size() << "/" << (uint16_t)calcBit(s.to_ulong()) << endl;
	
	for (int i = 0; i < 32; ++i)
	{
		bitset<10> s(i);
		cout << s.to_string() << " " << i << " " << (uint16_t)calcBit(i) << endl;
	}
	
	return 0;
}