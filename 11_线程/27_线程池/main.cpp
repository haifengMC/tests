//#define _D_AUTOPTR
//#define _D_AUTOPTR_DETAIL

#include "global.h"
#include "hSingleton.h"
#include "hThread.h"
#include "hThreadPoolMgr.h"
#include "hTest.h"
#include "test.h"

TEST_INIT()

using namespace std;
using namespace hThread;

TEST(任务枚举类型测试)
{
	TaskStatType e;
	cout << e.getName() << " " << e << endl;
	e = TaskStatType::Wait;
	cout << e.getName() << " " << e << endl;
}

TEST(线程池配置加载)
{
	ThreadPoolMgr& pool = sTreadPoolMgr;
}

TEST(读写锁测试)
{
	int iR = 1001;
	int iW = 1001;

	vector<thread> rwVec;
	for (; iR < 1011; ++iR)
		rwVec.emplace_back(readFunc, iR);
	vector<thread> wtVec;
	for (; iW <= 1011; ++iW)
		wtVec.emplace_back(writeFunc, iW);

	for (thread& thd : rwVec)
		thd.join();
	for (thread& thd : wtVec)
		thd.join();
}

TEST(智能指针测试1)
{
	vector<hTool::hAutoPtr<int>> v;
	cout << "......" << endl;
	v.push_back(new int(1));
	cout << "......" << endl;
	v.push_back(new int(2));
	cout << "......" << endl;
	v.push_back(new int(3));
	cout << "......" << endl;
	for (auto& i : v)
		cout << *i << endl;
}

TEST(智能指针测试2)
{
	list<hTool::hAutoPtr<int>> l;
	cout << "......" << endl;
	l.push_back(new int(1));
	cout << "......" << endl;
	l.push_back(new int(2));
	cout << "......" << endl;
	l.push_back(new int(3));
	cout << "......" << endl;
	for (auto& i : l)
		cout << *i << endl;
}

TEST(创建任务测试)
{
	Task t(new TaskAttr(50, 2, TaskAttrType::Loop));
}

TEST_MAIN()