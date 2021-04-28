#include <sstream>
#include <iostream>

using namespace std;

class Solution
{
	std::stringstream ss;
public:
	uint8_t char2Int(char ch)
	{
		switch (ch)
		{
		case '0': return 0;
		case '1': return 1;
		case '2': return 2;
		case '3': return 3;
		case '4': return 4;
		case '5': return 5;
		case '6': return 6;
		case '7': return 7;
		case '8': return 8;
		case '9': return 9;
		case '-': return -1;
		default: break;
		}

		return 0;
	}

	uint32_t pow10(uint8_t exp)
	{
		switch (exp)
		{
		case 0: return 1;
		case 1: return 10;
		case 2: return 100;
		case 3: return 1000;
		case 4: return 10000;
		case 5: return 100000;
		case 6: return 1000000;
		case 7: return 10000000;
		case 8: return 100000000;
		case 9: return 1000000000;
		default: break;
		}

		return 0;
	}

	int reverse1(int x)
	{
		ss.str("");
		char sign = 1;
		if (x < 0)
		{
			ss << -(int64_t)x;
			sign = -1;
		}
		else
			ss << x;

		const std::string& buf = ss.str();
		if (buf.size() > 9 && char2Int(buf.back()) > 2)
			return 0;

		int64_t n = 0;
		char exp = 0;
		char ch = 0;
		while (ss >> ch)
		{
			uint8_t chInt = char2Int(ch);
			if (!chInt)
			{
				++exp;
				continue;
			}

			n += chInt * pow10(exp++);
		}

		n *= sign;
		if (n > INT32_MAX || n < INT32_MIN)
			return 0;

		return n;
	}

	uint8_t fillBuf(uint8_t (&buf)[10], int x)
	{
		if (x < 0) x = -x;

		uint8_t n = 0;
		for (auto& ch : buf)
		{
			if (!x)
				break;

			ch = x % 10;
			x /= 10;
			++n;
		}

		return n;
	}

	uint8_t getN(uint8_t n)
	{
		switch (n)
		{
		case 0: return 2;
		case 1: return 1;
		case 2: return 4;
		case 3: return 7;
		case 4: return 4;
		case 5: return 8;
		case 6: return 3;
		case 7: return 6;
		case 8: return 4;
		default: break;
		}

		return 10;
	}

	bool checkBuf(uint8_t(&buf)[10])
	{
		for (int8_t i = 0; i < 10; ++i)
		{
			uint8_t n = getN(i);
			if (n == buf[i])
				continue;
			else
				return n > buf[i];
		}
	}

	int outBuf(uint8_t(&buf)[10], uint8_t n)
	{
		int out = 0;
		uint8_t exp = n - 1;
		for (int8_t i = 0; i < n; ++i, --exp)
			out += buf[i] * pow10(exp);

		return out;
	}

	int reverse(int x)
	{
		if (INT32_MIN == x)
			return 0;

		uint8_t buf[10] = {};
		uint8_t n = fillBuf(buf, x);
		if (n > 9 && !checkBuf(buf))
			return 0;

		return (x < 0 ? -1 : 1) * outBuf(buf, n);
	}
};

int main()
{
	Solution s;
	int buf = 1463847412;
	do
		cout << s.reverse(buf) << endl;
	while (cin >> buf);

	return 0;
}
