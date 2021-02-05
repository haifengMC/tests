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

TestNodeData::TestNodeData(const char* info)
{
	testInfo = info;
}

TestTaskNode::TestTaskNode(const char* info)
{
	testInfo = info;
}

void Test3A::addPtr(hTool::hAutoPtr<Test3C> pC)
{
	_pC = pC;
}

void Test3B::addPtr(hTool::hAutoPtr<Test3A> pA)
{
	_pA = pA;
}

void Test3C::addPtr(hTool::hAutoPtr<Test3B> pB)
{
	_pB = pB;
}

void Test4A::addPtr(hTool::hWeakPtr<Test4B> pB)
{
	Test4P(3);
	_pB = pB;
	Test4P(4);
}

void Test4B::addPtr(hTool::hWeakPtr<Test4A> pA)
{
	Test4P(6);
	_pA = pA;
	Test4P(7);
}

#undef COUT_LOCK