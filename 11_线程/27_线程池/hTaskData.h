#pragma once

namespace hThread
{
	namespace hTask
	{
		//任务静态数据管理(属性、节点静态数据)
		class hStaticDataMgr
		{
			DefLog_Init();
			hStatic::hAttrData _attrData;
			hStatic::hNodeData _nodeData;

		public:
			size_t getWeight() const { return _attrData.getWeight(); }
			void setAttr(const std::bitset<TaskAttrType::Max>& attr) { _attrData.setAttr(attr); }
			bool checkAttr(TaskAttrType attr) const { return _attrData.checkAttr(attr); }
			//增加任务节点
			bool addNode(hNode* pNode) { return _nodeData.addNode(pNode); }
			//初始化节点数据
			bool initNodeData(hStatic::hNodeData* pData = NULL) { return _nodeData.initNodeData(pData); }
			hNodeListIt getBegNodeIt() { return _nodeData.getBegNodeIt(); }
			hNodeListIt getEndNodeIt() { return _nodeData.getEndNodeIt(); }

			hStaticDataMgr(size_t weight, size_t thrdExpect, const std::bitset<TaskAttrType::Max>& attr);
		};

		//任务动态数据管理(状态、运行数据)
		class hDynamicDataMgr
		{
			DefLog_Init();
			PWhTask _pTask;	//指向自己所在任务
			PWhTaskMgr _pMgr;//指向自己所在管理器

			hDynamic::hStatData _state;//任务状态数据
			hDynamic::hRunData _run;//任务运行数据

		public:
			const char* getStatName() const { return _state.getStatName(); }
			//设置状态
			void setStat(TaskStatType stat) { _state.setStat(stat); }
			//检测状态
			bool checkStat(TaskStatType stat) const { return _state.checkStat(stat); }
			bool updateStat(TaskStatType stat) { return _state.updateStat(stat); }
			//重置状态数据
			void resetData() { _run.resetData(); }
			//获取下一个节点
			hNodeListIt getNextNodeIt(hNodeListIt beg, hNodeListIt end);

			hDynamicDataMgr(PWhTaskMgr pMgr, PWhTask pTask);
		};

		namespace hStatic
		{
			//属性数据
			struct hAttrData : public hDataBase
			{
				size_t _weight = 0;//权重
				size_t _thrdExpect = 0;//期待线程数
				std::bitset<TaskAttrType::Max> _attr;//任务属性，对应 TaskAttrType

				size_t getWeight() const;
				void setAttr(const std::bitset<TaskAttrType::Max>& attr);
				bool checkAttr(TaskAttrType attr) const;
			};

			//静态节点数据
			struct hNodeData : public hDataBase
			{
				size_t _incId = 0;//节点递增id

				PhUserData _nodeData;//节点数据
				hNodeList _nodeList;//节点链表

				bool addNode(hNode* pNode);//增加任务节点
				bool initNodeData(hUserData* pData);

				hNodeListIt getBegNodeIt();
				hNodeListIt getEndNodeIt();
			};
		}

		namespace hDynamic
		{
			//任务状态数据
			struct hStatData : public hDataBase
			{
				PWhTask _pTask;	//指向自己所在任务
				PWhTaskMgr _pMgr;//指向自己所在管理器

				TaskStatType _stateTy = TaskStatType::Max;//当前状态
				std::list<size_t>::iterator _stateIt;//指向当前状态的迭代器

				const char* getStatName() const;
				void setStat(TaskStatType stat);
				bool updateStat(TaskStatType stat);
				bool checkStat(TaskStatType stat)  const;

				hStatData(PWhTaskMgr pMgr, PWhTask pTask);
			};

			//任务运行数据
			struct hRunData :public hDataBase
			{
				PWhTask _pTask;	//指向自己所在任务
				PWhTaskMgr _pMgr;//指向自己所在管理器

				hMemWorkList _thrds;//当前运行该任务的工作线程
				hNodeListIt
					_curNodeIt,//指向当前在运行节点
					_nodeIt;//指向最后载入线程的节点

				//重置状态数据
				void resetData() { writeLk([&]() { _curNodeIt = _nodeIt = hNodeListIt(); }); }
				hNodeListIt getNextNodeIt(hNodeListIt beg, hNodeListIt end, bool isLoop);

				hRunData(PWhTaskMgr pMgr, PWhTask pTask);
			};
		}
	}
}
DefLog(hThread::hTaskStaticData, _weight, _thrdExpect, _incId, _attr, _nodeData, _nodeList);
DefLog(hThread::hTaskDynamicData, _stateTy, _stateIt, _pMgr, _thrds, _curNodeIt, _nodeIt);
