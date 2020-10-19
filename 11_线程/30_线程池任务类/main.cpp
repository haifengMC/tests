#include "global.h"
#include "hTool.h"
#include "hTest.h"
#include "hTask.h"

using namespace std;
TEST_INIT(Tst, testAll)

TEST(Tst, tst1)
{
	map<size_t, Task> m;
	hTool::hUniqueIdGen<size_t, Task> gen(m, 10, 1, 100);
	
	hTool::hAutoPtr<TaskAttr> attr;
	attr.emplace();
	cout << attr << endl;
	
	gen << Task(attr);
	gen << Task(attr);
	gen << Task(attr);

	cout << gen << endl;
}

TEST_MAIN(testAll)