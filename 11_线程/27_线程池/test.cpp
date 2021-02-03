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

std::ostream& TestNodeData::debugShow(std::ostream& os, uint8_t n, char c)
{
	Base::debugShow(os, n++, c) << std::endl;
	os << std::string(n, c) << "[TestNodeData]" <<
		" testInfo:" << testInfo;

	return os;
}

TestTaskNode::TestTaskNode(const char* info)
{
	testInfo = info;
}

std::ostream& TestTaskNode::debugShow(std::ostream& os, uint8_t n, char c)
{
	Base::debugShow(os, n++, c) << std::endl;
	os << std::string(n, c) << "[TestTaskNode]" <<
		" testInfo:" << testInfo;

	return os;
}

void TestA::addThis(hTool::hAutoPtr<TestB> pB)
{
	_pB = pB;
	_pB->_pA = this;
}

void TestA::destoryPtr()
{
	_pB.~hAutoPtr();
}

void TestB::destoryPtr()
{
	_pA.~hAutoPtr();
}

#undef COUT_LOCK