#include "global.h"
#include "hTest.h"

using namespace std;
TEST_INIT(Tst, testAll)

#define CNT 1000

void func1(int& i) 
{
	if (0 >= i)
		return;
	--i;
	func1(i);
}

void func2(int* i)
{
	if (0 >= *i)
		return;
	--* i;
	func2(i);
}

int i1 = CNT;
int i2 = CNT;
int i3 = CNT;
int i4 = CNT;
int i5 = CNT;
int i6 = CNT;

TEST(Tst, Tst1)
{
	func1(i1);
}

TEST(Tst, Tst2)
{
	func1(i2);
}

TEST(Tst, Tst3)
{
	func1(i3);
}

TEST(Tst, Tst4)
{
	func2(&i4);
}

TEST(Tst, Tst5)
{
	func2(&i5);
}

TEST(Tst, Tst6)
{
	func2(&i6);
}

int main()
{
	testAll();

	return 0;
}