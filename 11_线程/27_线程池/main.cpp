#include "global.h"
#include "hSingleton.h"
#include "hThread.h"
#include "hThreadPoolMgr.h"
#include "hTest.h"

TEST_INIT()

using namespace std;
using namespace hThread;

mutex coutM;
#define COUT_LOCK(x, ret) { lock_guard<mutex> lk(coutM); cout << "[" << i << "]" << #x << ret << endl; }

TEST(任务枚举类型测试)
{
	TaskStateType e;
	cout << e.getName() << " " << e << endl;
	e = TaskStateType::Wait;
	cout << e.getName() << " " << e << endl;
}

TEST(线程池配置加载)
{
	ThreadPoolMgr& pool = sTreadPoolMgr;
}

hRWLockItem m(hWLockIdType::Test);

void readFunc(int i)
{

	COUT_LOCK(rLk.....:, m.rdCnt << " " << m.wtId << " " << m.waiting << " " << m.writing);
	m.readLock();
	COUT_LOCK(r.......:, m.rdCnt << " " << m.wtId << " " << m.waiting << " " << m.writing);
	m.readUnlock();
	COUT_LOCK(rULk....:, m.rdCnt << " " << m.wtId << " " << m.waiting << " " << m.writing)
}

void writeFunc(int i)
{
	uint64_t id = hWLockId::addId(hWLockIdType::Test);

	COUT_LOCK(wLk.....:, "[" << id << "]" << m.rdCnt << " " << m.wtId << " " << m.waiting << " " << m.writing);
	bool ret = m.writeLock(id);
	if (ret)
	{
		//this_thread::sleep_for(chrono::seconds(1));
		COUT_LOCK(w.......:, "[" << id << "]" << m.rdCnt << " " << m.wtId << " " << m.waiting << " " << m.writing);
		m.writeUnlock();
		COUT_LOCK(wULk....:, "[" << id << "]" << m.rdCnt << " " << m.wtId << " " << m.waiting << " " << m.writing);
	}
	else
		COUT_LOCK(wFail...:, "[" << id << "]" << m.rdCnt << " " << m.wtId << " " << m.waiting << " " << m.writing);
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

TEST(Tst2)
{
	//hThread::ThreadPool& pool = sThreadPool;
	//this_thread::sleep_for(chrono::seconds(20));
}

#undef COUT_LOCK
TEST_MAIN()