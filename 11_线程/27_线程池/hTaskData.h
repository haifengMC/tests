#pragma once

namespace hThread
{
		//任务静态数据(属性、节点静态数据)
		struct hTaskStaticData
		{
			DefLog_Init();
			size_t _weight = 0;//权重
			size_t _thrdExpect = 0;//期待线程数

			size_t _incId = 0;//节点递增id
			std::bitset<TaskAttrType::Max> _attr;//任务属性，对应 TaskAttrType
			PhNodeData _nodeData;//节点数据
			hNodeList _nodeList;//节点链表

			void setAttr(const std::bitset<TaskAttrType::Max>& attr) { _attr = attr; }
			bool addNode(hNode* pNode);//增加任务节点
			bool initNodeData(hNodeData* pData = NULL);//初始化节点数据

			hTaskStaticData(size_t weight, size_t thrdExpect, const std::bitset<TaskAttrType::Max>& attr);
		};

		struct hTaskStatData : public hDataBase
		{
			PWhTask _pTask;	//指向自己所在任务
			PWhTaskMgr _pMgr;//指向自己所在管理器

			size_t _taskId = 0;	//任务id
			TaskStatType _stateTy = TaskStatType::Max;//当前状态
			std::list<size_t>::iterator _stateIt;//指向当前状态的迭代器

			hTaskStatData(PWhTaskMgr pMgr, PWhTask pTask);
		};

		//任务状态(运行时数据)
		struct hTaskDynamicData
		{
			DefLog_Init();
			PWhTask _pTask;	//指向自己所在任务
			PWhTaskMgr _pMgr;//指向自己所在管理器
			
			hTaskStatData _state;//任务状态数据
			
			hMemWorkList _thrds;//当前运行该任务的工作线程
			hNodeListIt
				_curNodeIt,//指向当前在运行节点
				_nodeIt;//指向最后载入线程的节点

			bool checkStat(TaskStatType stat);
			//重置状态数据
			void resetData() { _curNodeIt = _nodeIt = hNodeListIt(); }
			~hTaskDynamicData() {}//需要实现析构
		};
	

}
DefLog(hThread::hTaskStaticData, _weight, _thrdExpect, _incId, _attr, _nodeData, _nodeList);
DefLog(hThread::hTaskDynamicData, _stateTy, _stateIt, _pMgr, _thrds, _curNodeIt, _nodeIt);
