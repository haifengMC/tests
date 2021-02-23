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

bool Test1TaskNode::onProc()
{
	COUT_LK(_id << " 任务节点处理onProc()...");
	std::this_thread::sleep_for(1s);
	return true;
}

void Test2TaskData::update(size_t opt, ...)
{
	const char* s;
	va_list arg_ptr;
	va_start(arg_ptr, opt);
	s = va_arg(arg_ptr, decltype(s));
	va_end(arg_ptr);
	_s = s;
	COUT_LK("test2任务update() 更新数据" << _s << "...");
}

bool Test2TaskNode::preProc()
{
	if (!_s.empty())
		_s.clear();

	hTool::hWeakPtr<Test2TaskData> pData = _data.dynamic<Test2TaskData>();
	if (!pData)
	{
		COUT_LK("test2任务preProc() 数据未初始化为Test2TaskData对象...");
		return false;
	}

	std::swap(pData->_s, _s);
	return true;
}


bool Test2TaskNode::onProc()
{
	COUT_LK(_s);
	std::this_thread::sleep_for(1s);
	return true;
}

bool Test2TaskNode::finalProc()
{
	if (!_s.empty())
		_s.clear();
	return true;
}

Test2Task::Test2Task() : Task(50, 1, TaskAttrTypeBit::Repeat)
{
	initNodeData(new Test2TaskData);
	addNode(new Test2TaskNode);
}

bool Test2Task::canRepeat()
{
	if (!check())
	{
		checkErrOut();
		return false;
	}

	hTool::hWeakPtr<Test2TaskData> pData = 
		getAttr()->_nodeData.dynamic<Test2TaskData>();
	if (!pData)
	{
		COUT_LK("test2任务canRepeat() 数据未初始化为Test2TaskData对象...");
		return false;
	}

	return !pData->_s.empty();
}

#undef COUT_LOCK
