#pragma once

namespace hThread
{
	namespace hTaskMgr
	{
		//配置数据
		class hCfgData : public hDataBase
		{
			DefLog_Init();
			PWhTaskMgr _pMgr;//指向自己所在管理器
			const TaskMgrCfgItem& _base;
		public:
			TaskMgrPriority getId() const;
			const char* getName() const;
			size_t getMaxBusyThd() const;

			hCfgData(PWhTaskMgr pMgr, const TaskMgrCfgItem& base);
		};

		//任务管理数据
		class hTaskMgrData : public hTool::hUniqueIdGen<size_t, hTaskBase>, public hDataBase
		{
			DefLog_Init();
			PWhTaskMgr _pMgr;//指向自己所在管理器
		public:
			auto insertTask(PhTask pTask) ->
				std::pair<std::map<size_t, hTool::hAutoPtr<hTaskBase>>::iterator, bool>;
			PhTask getTask(size_t tskId);
			
			hTaskMgrData(PWhTaskMgr pMgr);
		};

		//权重管理数据
		class hWeightMgrData : public hTool::hRWeightMap<size_t>, public hDataBase
		{
			DefLog_Init();
			PWhTaskMgr _pMgr;//指向自己所在管理器
		public:
			//随机获取一个任务
			size_t getTaskAtRand();

			void pushTask(size_t weight, size_t tskId);
			void pushTask(PhTask pTask);
			void pushTask(PWhTask pTask);

			hWeightMgrData(PWhTaskMgr pMgr);
		};

		//状态管理数据
		class hStatMgrData : public hDataBase
		{
			DefLog_Init();
			PWhTaskMgr _pMgr;//指向自己所在管理器
			std::list<size_t> _states[TaskStatType::Max];//状态管理<thisId>
			std::map<size_t, TaskStatType> _stateMap;//状态map<thisId state>
		public:
			bool updateState(size_t tskId, std::list<size_t>::iterator statIt,
				TaskStatType oldStat, TaskStatType newStat);

			std::list<size_t>::iterator pushTask(PhTask pTask);

			hStatMgrData(PWhTaskMgr pMgr);
		};

		//更新管理数据
		class hUpdateMgrData : public hDataBase
		{
			DefLog_Init();
			PWhTaskMgr _pMgr;//指向自己所在管理器
			size_t _updateId = 0;//数据更新 任务id
		public:
			void setId(size_t id);
			size_t getId() const;

			hUpdateMgrData(PWhTaskMgr pMgr);
		};
	}
}
DefLog(hThread::hTaskMgr::hCfgData, _pMgr, _base);
DefLog(hThread::hTaskMgr::hTaskMgrData, _pMgr, _minN, _maxN, _curN, _genRange, _keySet, _mapData);
DefLog(hThread::hTaskMgr::hWeightMgrData, _pMgr, _total, _weights);
DefLog(hThread::hTaskMgr::hStatMgrData, _pMgr, _states, _stateMap);
DefLog(hThread::hTaskMgr::hUpdateMgrData, _pMgr, _updateId);