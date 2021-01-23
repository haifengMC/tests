#include "global.h"
#include "hSingleton.h"
#include "hThread.h"
#include "hThreadPoolMgr.h"
#include "test.h"

using namespace std;
using namespace hThread;
mutex coutM;
#define COUT_LOCK(x, ret) { lock_guard<mutex> lk(coutM); cout << "[" << i << "]" << #x << ret << endl; }

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

#undef COUT_LOCK