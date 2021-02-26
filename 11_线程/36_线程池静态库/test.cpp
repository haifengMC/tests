#include "global.h"
#include "hThread.h"
#include "hThread/hThreadPoolMgr.h"
#include "test.h"

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
	std::this_thread::sleep_for(std::chrono::seconds(1));
	return true;
}

bool Test2TaskNode::finalProc()
{
	if (!_s.empty())
		_s.clear();
	return true;
}

Test2Task::Test2Task() : hTask(50, 1, TaskAttrTypeBit::Repeat)
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
