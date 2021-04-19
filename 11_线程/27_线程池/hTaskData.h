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
			size_t getNeedThrdNum() const { return std::min(_attrData.getExpectThrd(), _nodeData.getNodeNum()); }
			size_t getAttr() const { return _attrData.getAttr(); }
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
			hNodeListIt getNextNodeIt(hNodeListIt beg, hNodeListIt end, bool isLoop) { return _run.getNextNodeIt(beg, end, isLoop); }
			//添加线程到任务,还未启用
			hMemWorkListIt addThrdMem(PWhMemWork pMem) { return _run.addThrdMem(pMem); }
			//初始化当前运行节点
			void initCurNodeIt(hNodeListIt initIt) { _run.initCurNodeIt(initIt); }
			//完成当前节点，通知下一个线程
			bool finishCurNode(hMemWorkListIt memIt, hNodeListIt beg, hNodeListIt end, bool isLoop);
			//任务节点分配完成释放线程
			void freeThrdMem(hMemWorkListIt memIt, hNodeListIt end, size_t attr);
			//更新任务数据
			template <typename ... Args >
			void updateTaskData(size_t opt, Args ... args);

			hDynamicDataMgr(PWhTaskMgr pMgr, PWhTask pTask);
		};

		namespace hStatic
		{
			//属性数据
			struct hAttrData : public hDataBase
			{
				size_t _weight = 0;//权重
				size_t _expectThrd = 0;//期待线程数
				std::bitset<TaskAttrType::Max> _attr;//任务属性，对应 TaskAttrType

				size_t getWeight() const;
				size_t getExpectThrd() const;
				size_t getAttr() const;
				void setAttr(const std::bitset<TaskAttrType::Max>& attr);
				bool checkAttr(TaskAttrType attr) const;
			};

			//静态节点数据
			struct hNodeData : public hDataBase
			{
				size_t _incId = 0;//节点递增id

				PhUserData _nodeData;//节点数据
				hNodeList _nodeList;//节点链表

				size_t getNodeNum() const;
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
				//添加线程到任务,还未启用
				hMemWorkListIt addThrdMem(PWhMemWork pMem);
				//初始化当前运行节点
				void initCurNodeIt(hNodeListIt initIt);
				bool isValidNodeIt(hNodeListIt end);
				bool isValidThrdIt(hMemWorkListIt memIt);
				//递增当前运行节点
				void incCurNodeIt(hNodeListIt beg, hNodeListIt end, bool isLoop);
				//任务节点分配完成释放线程
				void eraseThrdMem(hMemWorkListIt memIt);
				//检测完成状态
				TaskStatType checkFinishState(hNodeListIt end, size_t attr) const;
				hMemWorkListIt getBegThrdIt();
				hMemWorkListIt getEndThrdIt();

				hRunData(PWhTaskMgr pMgr, PWhTask pTask);
			};
		}
	}
}
DefLog(hThread::hTask::hStatic::hAttrData, _weight, _expectThrd, _attr);
DefLog(hThread::hTask::hStatic::hNodeData, _incId, _nodeData, _nodeList);
DefLog(hThread::hTask::hStaticDataMgr, _attrData, _nodeData);
DefLog(hThread::hTask::hDynamic::hStatData, _stateTy, _stateIt);
DefLog(hThread::hTask::hDynamic::hRunData, _thrds, _curNodeIt, _nodeIt);
DefLog(hThread::hTask::hDynamicDataMgr, _pTask, _pMgr, _state, _run);
