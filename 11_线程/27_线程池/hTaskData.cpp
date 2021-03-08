#include "global.h"
#include "hThread.h"
#include "hPoolMgr.h"

namespace hThread
{
	bool hTaskStaticData::addNode(hNode* pNode)
	{
		if (!pNode)
			return false;

		if (!_nodeData)
			return false;

		pNode->init(++_incId, _nodeData);

		_nodeList.push_back(hTool::hAutoPtr<hNode>(pNode));
		return pNode;
	}

	bool hTaskStaticData::initNodeData(hNodeData* pData)
	{
		if (pData)
			_nodeData.bind(pData);
		else
			_nodeData.emplace();

		return true;
	}

	hTaskStaticData::hTaskStaticData(size_t weight, size_t thrdExpect, const std::bitset<TaskAttrType::Max>& attr)
	{
		_weight = weight;
		_thrdExpect = thrdExpect;
		_attr = attr;
	}

	bool hTaskStatData::checkStat(TaskStatType stat) const
	{
		if (TaskStatType::Max <= stat)
			return false;

		bool ret = true;
		readLk([&]() { ret = _dynData->_stateTy == stat; });
		return ret;
	}

	hTaskStatData::hTaskStatData(PWhTaskMgr pMgr, PWhTask pTask)
	{
		_pMgr = pMgr;
		_pTask = pTask;
	}

	hTaskRunData::hTaskRunData(PWhTaskMgr pMgr, PWhTask pTask)
	{
		_pMgr = pMgr;
		_pTask = pTask;
	}

	hTaskDynamicData::hTaskDynamicData(PWhTaskMgr pMgr, PWhTask pTask) :
		_state(pMgr, pTask), _run(pMgr, pTask)
	{
		_pMgr = pMgr;
		_pTask = pTask;
	}
}