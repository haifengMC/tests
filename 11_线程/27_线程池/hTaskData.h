#pragma once

namespace hThread
{
	namespace hTask
	{
		struct hAttrData;//属性数据
		struct hStcNodeData;//静态节点数据
	}
	struct hTaskStatData;//任务状态数据
	struct hTaskRunData;//任务运行数据

	//任务静态数据(属性、节点静态数据)
	struct hTaskStaticData
	{
		DefLog_Init();

		hTask::hAttrData _attr;
		hTask::hStcNodeData _node;

		void setAttr(const std::bitset<TaskAttrType::Max>& attr) { _attr = attr; }
		bool addNode(hNode* pNode);//增加任务节点
		bool initNodeData(hNodeData* pData = NULL);//初始化节点数据

		hTaskStaticData(size_t weight, size_t thrdExpect, const std::bitset<TaskAttrType::Max>& attr);
	};

	//动态数据
	struct hTaskDynamicData
	{
		DefLog_Init();
		PWhTask _pTask;	//指向自己所在任务
		PWhTaskMgr _pMgr;//指向自己所在管理器
			
		hTaskStatData _state;//任务状态数据
		hTaskRunData _run;//任务运行数据

		//检测状态
		bool checkStat(TaskStatType stat) const { return _state.checkStat(stat); }
		//重置状态数据
		void resetData() { _run.resetData(); }

		hTaskDynamicData(PWhTaskMgr pMgr, PWhTask pTask);
		~hTaskDynamicData() {}//需要实现析构
	};

	namespace hTask
	{
		//属性数据
		struct hAttrData : public hDataBase
		{
			size_t _weight = 0;//权重
			size_t _thrdExpect = 0;//期待线程数
			std::bitset<TaskAttrType::Max> _attr;//任务属性，对应 TaskAttrType
		};

		//静态节点数据
		struct hStcNodeData : public hDataBase
		{
			size_t _incId = 0;//节点递增id

			PhNodeData _nodeData;//节点数据
			hNodeList _nodeList;//节点链表
		};

	}

	//任务状态数据
	struct hTaskStatData : public hDataBase
	{
		PWhTask _pTask;	//指向自己所在任务
		PWhTaskMgr _pMgr;//指向自己所在管理器

		TaskStatType _stateTy = TaskStatType::Max;//当前状态
		std::list<size_t>::iterator _stateIt;//指向当前状态的迭代器

		bool checkStat(TaskStatType stat)  const;

		hTaskStatData(PWhTaskMgr pMgr, PWhTask pTask);
	};

	//任务运行数据
	struct hTaskRunData :public hDataBase
	{
		PWhTask _pTask;	//指向自己所在任务
		PWhTaskMgr _pMgr;//指向自己所在管理器

		hMemWorkList _thrds;//当前运行该任务的工作线程
		hNodeListIt
			_curNodeIt,//指向当前在运行节点
			_nodeIt;//指向最后载入线程的节点

		//重置状态数据
		void resetData() { writeLk([&]() { _curNodeIt = _nodeIt = hNodeListIt(); }); }

		hTaskRunData(PWhTaskMgr pMgr, PWhTask pTask);
	};
}
DefLog(hThread::hTaskStaticData, _weight, _thrdExpect, _incId, _attr, _nodeData, _nodeList);
DefLog(hThread::hTaskDynamicData, _stateTy, _stateIt, _pMgr, _thrds, _curNodeIt, _nodeIt);
