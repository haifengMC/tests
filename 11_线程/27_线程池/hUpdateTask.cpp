#include "global.h"
#include "hTool.h"
#include "hThread.h"
#include "hThreadPoolMgr.h"

namespace hThread
{
	bool UpdateTaskNode::preProc()
	{
		if (!_execList.empty())
			_execList.clear();

		PWUpdTskDt pData = _data.dynamic<UpdateTaskData>();
		if (!pData)
		{
			COUT_LK("数据更新任务 数据未初始化为UpdateTaskData对象...");
			return false;
		}

		std::swap(pData->_updateList, _execList);
		return true;
	}

	bool UpdateTaskNode::onProc()
	{
		for (auto& fn : _execList)
			fn();
		sThrdPool.notifyMgrThrd();
		return true;
	}

	bool UpdateTaskNode::finalProc()
	{
		if (!_execList.empty())
			_execList.clear();
		return true;
	}

	UpdateTask::UpdateTask() : Task(50, 1, TaskAttrTypeBit::Repeat)
	{
		initNodeData(new UpdateTaskData);
		addNode(new UpdateTaskNode);
	}

	void UpdateTask::updata(std::function<void()>& fn)
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
					COUT_LK("数据更新任务 数据未初始化为UpdateTaskData对象...");
					return;
				}
				
				pData->_updateList.push_back(fn);
			});
	}

}