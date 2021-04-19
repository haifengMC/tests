#pragma once

namespace hThread
{
	namespace hTaskMgr
	{
		//配置数据
		class hCfgData : public hDataBase
		{
			PWhTaskMgr _pMgr;//指向自己所在管理器
			const TaskMgrCfgItem& _base;
		public:
			hCfgData(PWhTaskMgr pMgr, const TaskMgrCfgItem& base);
		};

		//任务管理数据
		class hTaskMgrData : public hTool::hUniqueIdGen<size_t, hTaskBase>, public hDataBase
		{
			PWhTaskMgr _pMgr;//指向自己所在管理器
		public:
			hTaskMgrData(PWhTaskMgr pMgr);
		};

		//权重管理数据
		class hWeightMgrData : public hTool::hRWeightMap<size_t>, public hDataBase
		{
			PWhTaskMgr _pMgr;//指向自己所在管理器
		public:
			void pushTask(size_t weight, size_t tskId);
			void pushTask(PWhTask pTask);

			hWeightMgrData(PWhTaskMgr pMgr);
		};

		//状态管理数据
		class hStatMgrData : public hDataBase
		{
			PWhTaskMgr _pMgr;//指向自己所在管理器
			std::list<size_t> _states[TaskStatType::Max];//状态管理<thisId>
			std::map<size_t, TaskStatType> _stateMap;//状态map<thisId state>
		public:
			std::list<size_t>* getStateList(TaskStatType state);
			bool updateState(size_t tskId, std::list<size_t>::iterator& statIt,
				TaskStatType oldStat, TaskStatType newStat);

			hStatMgrData(PWhTaskMgr pMgr);
		};

		//更新管理数据
		class hUpdateMgrData : public hDataBase
		{
			PWhTaskMgr _pMgr;//指向自己所在管理器
			size_t _updateId = 0;//数据更新 任务id
		public:
			hUpdateMgrData(PWhTaskMgr pMgr);
		};
	}
}
