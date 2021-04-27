#include "global.h"
#include "hSingleton.h"
#include "hThread.h"
#include "hPoolMgr.h"
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

bool Test1TaskNode::onProc()
{
	COUT_LK(_id << " ����ڵ㴦��onProc()...");
	std::this_thread::sleep_for(1s);
	return true;
}

void Test2TaskData::update(size_t opt, void* data, size_t len)
{
	const char* s = (const char*)data;
	if (s)
	{
		_sLst.push_back(s);
		COUT_LK("test2����update() ��������" << opt << ":" << s << "...");
	}
	else
		COUT_LK("test2����update() ����ʧ��" << opt << "...");
}

bool Test2TaskNode::preProc()
{
	COUT_LK("test2����preProc()...");
	hTool::hWeakPtr<Test2TaskData> pData = _data.dynamic<Test2TaskData>();
	if (!pData)
	{
		COUT_LK("test2����preProc() ����δ��ʼ��ΪTest2TaskData����...");
		return false;
	}

	if (pData->_sLst.empty())
	{
		COUT_LK("test2����preProc() �ַ����б�Ϊ��...");
		return false;
	}

	return true;
}


bool Test2TaskNode::onProc()
{
	COUT_LK(OUTCOL_GREEN("test2����onProc()..."));
	COUT_LK("test2����onProc()...");
	hTool::hWeakPtr<Test2TaskData> pData = _data.dynamic<Test2TaskData>();
	if (!pData)
	{
		COUT_LK("test2����onProc() ����δ��ʼ��ΪTest2TaskData����...");
		return false;
	}

	std::swap(pData->_sLst.front(), _s);
	pData->_sLst.pop_front();

	std::cout << "�����..." << std::endl;
	std::this_thread::sleep_for(1s);
	std::cout << "������:" << _s << " ʣ��:" << pData->_sLst.size() << std::endl;
	std::this_thread::sleep_for(1s);
	std::cout << "������" << std::endl;
	return true;
}

bool Test2TaskNode::finalProc()
{
	COUT_LK("test2����finalProc()...");
	if (!_s.empty())
		_s.clear();
	return true;
}

Test2Task::Test2Task() : hTaskBase(50, 1, TaskAttrTypeBit::Repeat)
{
	initNodeData(new Test2TaskData);
	addNode(new Test2TaskNode);
}

bool Test2Task::canRepeat() const
{
	if (!check())
	{
		checkErrOut();
		return false;
	}

	hTool::hWeakPtr<const Test2TaskData> pData = getUserData<Test2TaskData>();
	if (!pData)
	{
		COUT_LK("test2����canRepeat() ����δ��ʼ��ΪTest2TaskData����...");
		return false;
	}

	return !pData->_sLst.empty();
}

#undef COUT_LOCK
