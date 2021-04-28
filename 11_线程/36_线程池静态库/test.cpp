#include "global.h"
#include "hThread.h"
#include "hThread/hPoolMgr.h"
#include "test.h"

void Test2TaskData::update(size_t opt, void* data, size_t len)
{
	const char* s = (const char*)data;
	if (s)
	{
		_sLst.push_back(s);
		COUT_LK("test2任务update() 更新数据" << opt << ":" << s << "...");
	}
	else
		COUT_LK("test2任务update() 更新失败" << opt << "...");
}

bool Test2TaskNode::preProc()
{
	COUT_LK("test2任务preProc()...");
	hTool::hWeakPtr<Test2TaskData> pData = _data.dynamic<Test2TaskData>();
	if (!pData)
	{
		COUT_LK("test2任务preProc() 数据未初始化为Test2TaskData对象...");
		return false;
	}

	if (pData->_sLst.empty())
	{
		COUT_LK("test2任务preProc() 字符串列表为空...");
		return false;
	}

	return true;
}


bool Test2TaskNode::onProc()
{
	COUT_LK(OUTCOL_GREEN("test2任务onProc()..."));
	COUT_LK("test2任务onProc()...");
	hTool::hWeakPtr<Test2TaskData> pData = _data.dynamic<Test2TaskData>();
	if (!pData)
	{
		COUT_LK("test2任务onProc() 数据未初始化为Test2TaskData对象...");
		return false;
	}

	std::swap(pData->_sLst.front(), _s);
	pData->_sLst.pop_front();

	std::cout << "输出中..." << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "输出结果:" << _s << " 剩余:" << pData->_sLst.size() << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "输出完成" << std::endl;
	return true;
}

bool Test2TaskNode::finalProc()
{
	COUT_LK("test2任务finalProc()...");
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
		COUT_LK("test2任务canRepeat() 数据未初始化为Test2TaskData对象...");
		return false;
	}

	return !pData->_sLst.empty();
}
