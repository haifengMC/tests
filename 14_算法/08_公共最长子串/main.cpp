#include <string>
#include <list>
#include <iostream>

using namespace std;

//longest common sequence
struct LCSPos
{
	string::size_type _pos1 = string::npos;
	string::size_type _pos2 = string::npos;
	string _subStr;
};

struct LCSData
{
	size_t _len = 0;
	list<LCSPos> _posList;

	const string& _s1;
	const string& _s2;

	LCSData(string& s1, string& s2) : _s1(s1), _s2(s2) {}
	void solution()
	{


		for (auto ch1 : _s1)
		{
			for (auto _ch2 : _s2)
			{

			}
		}
	}
};


int main()
{


	return 0;
}