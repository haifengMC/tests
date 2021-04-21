#include "global.h"
#include "hTool.h"
#include "hThread.h"
#include "hPoolMgr.h"

namespace hThread
{
	void hUpdateData::updateTask(size_t taskId,
		std::function<bool()>& checkFn,
		std::function<void()>& execFn)
	{
		writeLk([&]()
			{
				auto it = _updateMap.find(taskId);
				if (it == _updateMap.end())
					_updateMap.insert(std::make_pair(taskId, UpdateTaskDefine::ItemData(taskId, checkFn, execFn)));
				else
					it->second._execList.push_back(execFn);
			});
	}

	bool UpdateTaskNode::preProc()
	{
		PWhUpdDt pData = _data.dynamic<hUpdateData>();
		if (!pData)
		{
			COUT_LK("���ݸ�������preProc() ����δ��ʼ��ΪUpdateTaskData����...");
			return false;
		}

		if (pData->_updateMap.empty())
		{
			COUT_LK("���ݸ�������preProc() �����������...");
			return false;
		}

		return true;
	}

	bool UpdateTaskNode::onProc()
	{
		PWhUpdDt pData = _data.dynamic<hUpdateData>();
		if (!pData)
			return false;

		COUT_LK("���ݸ������� �����������ݿ�ʼ...");
		for (auto it = pData->_updateMap.begin(); it != pData->_updateMap.end();)
		{
			auto& data = it->second;
			if (!data._checkFn())
			{
				++it;
				continue;
			}

			_execList.splice(_execList.end(), data._execList);
			it = pData->_updateMap.erase(it);
		}
		COUT_LK("���ݸ������� �����������ݽ���...");

		if (_execList.empty())
			return false;

		for (auto& fn : _execList)
			fn();
		shPool.notifyMgrThrd();
		return true;
	}

	bool UpdateTaskNode::finalProc()
	{
		_execList.clear();
		return true;
	}

	hUpdateTask::hUpdateTask() : hTaskBase(50, 1, TaskAttrTypeBit::Repeat)
	{
		initNodeData(new hUpdateData);
		addNode(new UpdateTaskNode);
	}

	void hUpdateTask::updata(size_t taskId,
		std::function<bool()>& checkFn,
		std::function<void()>& execFn)
	{
		if (!check())
		{
			checkErrOut();
			return;
		}

		PWhUpdDt pData = getUserData<hUpdateData>();
		if (!pData)
		{
			COUT_LK("���ݸ�������updata() ����δ��ʼ��ΪUpdateTaskData����...");
			return;
		}

		pData->updateTask(taskId, checkFn, execFn);
	}

	bool hUpdateTask::canRepeat()
	{
		if (!check())
		{
			checkErrOut();
			return false;
		}

		PWhUpdDt pData = getUserData<hUpdateData>();
		if (!pData)
		{
			COUT_LK("���ݸ�������canRepeat() ����δ��ʼ��ΪUpdateTaskData����...");
			return false;
		}

		return !pData->_updateMap.empty();
	}
}