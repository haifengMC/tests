#include "global.h"
#include "hSingleton.h"
#include "hThread.h"
#include "hTest.h"

#include "test.h"

TEST_INIT(Tst, testAll)


using namespace std;
string s = "hello";
hThread::hRWLock m;
mutex coutM;
#define COUT_LOCK(x, ret) { lock_guard<mutex> lk(coutM); cout << "[" << this_thread::get_id() << "]" << #x << ret << endl; }

void readFunc()
{

	COUT_LOCK(read lock---:, m.rdCnt << " " << m.wtCnt << " " << m.waiting);
	m.readLock();
	COUT_LOCK(read--------:, m.rdCnt << " " << m.wtCnt << " " << m.waiting);
	m.readUnlock();
	COUT_LOCK(read unlock-:, m.rdCnt << " " << m.wtCnt << " " << m.waiting)
}

void writeFunc()
{

	COUT_LOCK(write lock---:, m.rdCnt << " " << m.wtCnt << " " << m.waiting);
	m.writeLock();
	//std::this_thread::sleep_for(chrono::microseconds(20));
	COUT_LOCK(write--------:, m.rdCnt << " " << m.wtCnt << " " << m.waiting);
	m.writeUnlock();
	COUT_LOCK(write unlock-:, m.rdCnt << " " << m.wtCnt << " " << m.waiting);

}

TEST(Tst, Tst1)
{
	vector<thread> rwVec;
	for (int i = 1; i <= 10; ++i)
		rwVec.emplace_back(readFunc);
	vector<thread> wtVec;
	for (int i = 1; i <= 10; ++i)
		wtVec.emplace_back(writeFunc);

	for (thread& thd : rwVec)
		thd.join();
	for (thread& thd : wtVec)
		thd.join();
}

TEST(Tst, Tst2)
{
	hThread::ThreadPool& pool = sThreadPool;
	this_thread::sleep_for(chrono::seconds(20));
}