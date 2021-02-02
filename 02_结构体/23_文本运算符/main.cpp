#include <chrono>
#include <initializer_list>
#include <sstream>
#include <iostream>

using namespace std;

struct A
{
	size_t _i = 0;

	constexpr A(size_t i) { _i = i; }
};

constexpr A operator"" _sA(size_t i)
{
	return A(i);
}


struct RGBA
{
	uint8_t _r;
	uint8_t _g;
	uint8_t _b;
	uint8_t _a;
	constexpr RGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : 
		_r(r), _g(g), _b(b), _a(a) {}
};

constexpr RGBA operator "" _C(const char* col, size_t n)
{
	const char* p = col;
	const char* end = col + n;
	const char *r = NULL, *g = NULL, *b = NULL, *a = NULL;
	uint8_t rV = 0, gV = 0, bV = 0, aV = 0;
	for (; p != end; ++p)
	{
		switch (*p)
		{
		case 'r': r = p; break;
		case 'g': g = p; break;
		case 'b': b = p; break;
		case 'a': a = p; break;
		default: break;
		}
	}

	if (r) rV = atoi(r + 1);
	if (g) gV = atoi(g + 1);
	if (b) bV = atoi(b + 1);
	if (a) aV = atoi(a + 1);
	
	return RGBA(rV, gV, bV, aV);
}

ostream& operator<<(ostream& os, const RGBA& col)
{
	return os <<
		"r:" << (int)col._r << ", "
		"g:" << (int)col._g << ", "
		"b:" << (int)col._b << ", "
		"a:" << (int)col._a;
}

int main()
{
	A a = 1_sA;
	cout << a._i << endl;

	cout << "r255 g240 b155"_C << endl;
	cout << "r15 g255 b10 a7"_C << endl;


	return 0;
}