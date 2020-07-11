#include "global.h"
#include "hSingleton.h"
#include "hThread.h"
#include "hTest.h"

#include "test.h"

TEST_INIT(Tst, testAll)

TEST(Tst, Tst1)
{
	hThread::TreadPool& pPool = sTreadPool;
}