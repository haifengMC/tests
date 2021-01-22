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

TEST(����ö�����Ͳ���)
{
	TaskStateType e;
	cout << e.getName() << " " << e << endl;
	e = TaskStateType::Wait;
	cout << e.getName() << " " << e << endl;
}

TEST(�̳߳����ü���)
{
	ThreadPoolMgr& pool = sTreadPoolMgr;
}

hRWLock m(hWLockIdType::Test);

void readFunc(int i)
{
	m.readLock();
	COUT_LOCK(read, "");
	m.readUnlock();
}

void writeFunc(int i)
{
	uint64_t id = hWLockId::addId(hWLockIdType::Test);
	
	bool ret = m.writeLock(id);
	if (!ret)
	{
		COUT_LOCK(wFail, "[" << id << "]");
		return;
	}

	//this_thread::sleep_for(chrono::seconds(1));
	COUT_LOCK(wSucc, "[" << id << "]");
	m.writeUnlock();
}

TEST(��д������)
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