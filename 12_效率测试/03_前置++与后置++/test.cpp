#include "global.h"
#include "vcommon.h"
#include "hSingleton.h"
#include "hTest.h"
#include "hTool.h"
#include "test.h"

using namespace std;
TEST_INIT(Tst, testAll)

#define N 1000000

TEST(Tst, Tst1)
{
	for (size_t i = 0; i < N; ++i)
		;

	//cout << str2 << endl;
}

TEST(Tst, Tst2)
{
	for (size_t i = 0; i < N; i++)
		;
	//cout << str2 << endl;

}