#include "global.h"
#include "hTool.h"
#include "hTest.h"

using namespace std;
TEST_INIT() {}

class Solution {
public:
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

	uint8_t fillBuf(uint8_t(&buf)[10], int x)
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

		return false;
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
} s;

TEST(整数取反测试)
{
	size_t cnt = 0;
	int i = INT32_MIN;
	do 
	{
		s.reverse(i);

		if (++cnt > 100000000)
			break;

		if (i++ == INT32_MAX)
			break;
	} while (1);
}

TEST_MAIN()