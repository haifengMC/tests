#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

//longest common sequence
struct LCSPos
{
	size_t _pos1 = string::npos;
	size_t _pos2 = string::npos;
	string _subStr;
};

struct LCSData
{
	size_t _len = 0;
	list<LCSPos> _posList;

	const string& _s1;
	const string& _s2;

	LCSData(string& s1, string& s2) : _s1(s1), _s2(s2) {}
	void solution();
	void print();
};

int main()
{
	string s1 = "abab", s2="ab";
	
	do
	{
		LCSData dt(s1, s2);
		dt.solution();
		dt.print();
	} while (cin >> s1 >> s2);

	return 0;
}

void LCSData::solution()
{
	if (_s1.empty() || _s2.empty())
		return;

	vector<size_t> preBuf(_s2.size());
	vector<size_t> curBuf(_s2.size());

	for (size_t i1 = 0; i1 < _s1.size(); ++i1)
	{
		for (size_t i2 = 0; i2 < _s2.size(); ++i2)
		{
			curBuf[i2] = i1 && i2 ? preBuf[i2 - 1] : 0;

			if (_s1[i1] != _s2[i2])
				continue;

			++curBuf[i2];
			if (curBuf[i2] < max<size_t>(2, _len))
				continue;

			if (_len < curBuf[i2])
			{
				_len = curBuf[i2];
				_posList.clear();
			}

			_posList.emplace_back();
			_posList.back()._pos1 = i1 + 1 - _len;
			_posList.back()._pos2 = i2 + 1 - _len;
			_posList.back()._subStr = _s1.substr(i1 + 1 - _len, _len);
		}
		swap(preBuf, curBuf);
	}
}

void LCSData::print()
{
	cout << "s1:" << _s1 << endl;
	cout << "s2:" << _s2 << endl;
	cout << "len:" << _len << endl;

	for (auto& pos : _posList)
		cout << "[" << pos._pos1 << "," << pos._pos2 << "]" << pos._subStr << endl;
}