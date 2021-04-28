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
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "������:" << _s << " ʣ��:" << pData->_sLst.size() << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
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
