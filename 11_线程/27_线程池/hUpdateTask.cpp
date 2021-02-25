#include "global.h"
#include "hTool.h"
#include "hThread.h"
#include "hThreadPoolMgr.h"

namespace hThread
{
	bool UpdateTaskNode::preProc()
	{
		PWUpdTskDt pData = _data.dynamic<UpdateTaskData>();
		if (!pData)
		{
			COUT_LK("数据更新任务preProc() 数据未初始化为UpdateTaskData对象...");
			return false;
		}

		if (pData->_updateMap.empty())
		{
			COUT_LK("数据更新任务preProc() 数据无需更新...");
			return false;
		}

		return true;
	}

	bool UpdateTaskNode::onProc()
	{
		PWUpdTskDt pData = _data.dynamic<UpdateTaskData>();
		if (!pData)
			return false;

		COUT_LK("数据更新任务 检测待更新数据开始...");
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
		COUT_LK("数据更新任务 检测待更新数据结束...");

		if (_execList.empty())
			return false;

		for (auto& fn : _execList)
			fn();
		sThrdPool.notifyMgrThrd();
		return true;
	}

	bool UpdateTaskNode::finalProc()
	{
		_execList.clear();
		return true;
	}

	UpdateTask::UpdateTask() : Task(50, 1, TaskAttrTypeBit::Repeat)
	{
		initNodeData(new UpdateTaskData);
		addNode(new UpdateTaskNode);
	}

	void UpdateTask::updata(size_t taskId,
		std::function<bool()>& checkFn,
		std::function<void()>& execFn)
	{
		writeLk([&]() 
			{
				if (!check())
				{
					checkErrOut();
					return;
				}

				PWUpdTskDt pData = getAttr()->_nodeData.dynamic<UpdateTaskData>();
				if (!pData)
				{
					COUT_LK("数据更新任务updata() 数据未初始化为UpdateTaskData对象...");
					return;
				}
				
				auto it = pData->_updateMap.find(taskId);
				if (it == pData->_updateMap.end())
					pData->_updateMap.insert(std::make_pair(taskId, UpdateTaskDefine::ItemData(taskId, checkFn, execFn)));
				else
					it->second._execList.push_back(execFn);
			});
	}

	bool UpdateTask::canRepeat()
	{
		if (!check())
		{
			checkErrOut();
			return false;
		}

		PWUpdTskDt pData = getAttr()->_nodeData.dynamic<UpdateTaskData>();
		if (!pData)
		{
			COUT_LK("数据更新任务canRepeat() 数据未初始化为UpdateTaskData对象...");
			return false;
		}

		return !pData->_updateMap.empty();
	}
}