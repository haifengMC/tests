#pragma once

namespace hThread
{
	class hTaskMgrBase : public hTool::hAutoPtrObj
	{
		DefLog_Init();
		hTaskMgr::hCfgData _cfg;
		hTaskMgr::hTaskMgrData _taskMgr;//<id-Task>id生成器
		hTaskMgr::hWeightMgrData _weightMgr;//权重管理<task thisId>
		hTaskMgr::hStatMgrData _statMgr;//状态管理<thisId>
		hTaskMgr::hUpdateMgrData _updateMgr;//数据更新 任务id
	public:
		hTaskMgrBase(const TaskMgrCfgItem& base);
		~hTaskMgrBase();

	};


	class hTaskMgr : public hTool::hAutoPtrObj
	{
		const TaskMgrCfgItem& _base;

		hTool::hUniqueIdGen<size_t, hTask> _tasks;//<id-Task>id生成器
		hTool::hRWeightMap<size_t> _weights;//权重管理<task thisId>
		WeightsMgr _weightsMgr;//权重管理<task thisId>
		std::list<size_t> _states[TaskStatType::Max];//状态管理<thisId>
		hStatMgrData _stateMgr;//状态管理

		size_t _updateId = 0;//数据更新 任务id
	public:
		hTaskMgr(const TaskMgrCfgItem& base);
		~hTaskMgr();

		void init();

		//std::list<size_t>* getStateList(TaskStatType state) { return _stateMgr.getStateList(state); }
		std::list<size_t>* getStateList(TaskStatType state);

		//提交任务，将新任务提交给管理器，提交后默认状态为等待
		template <size_t N>
		size_t commitTasks(PhTask(&task)[N]);
		size_t commitTasks(PhTask* task, size_t num);
		size_t commitTasks(PhTask& task);
		//准备任务，按权重取出等待任务放入就绪任务，返回任务指针
		PhTask readyTasks(size_t busy);
		//更新任务数据
		template <typename ... Args >
		void updateTaskData(size_t taskId, size_t opt, Args ... args);

		//更新任务状态
		bool updateTaskState(size_t tskId, std::list<size_t>::iterator& statIt,
			TaskStatType oldStat, TaskStatType newStat);
		//将任务加入
		void pushTask2Weights(PWhTask pTask) { _weightsMgr.pushTask(pTask); }

	private:
		//向更新任务添加函数
		void addUpdateTaskFunc(size_t taskId, 
			std::function<bool()> checkFn,
			std::function<void()> execFn);

		void spliceTasks(TaskStatType from, TaskStatType to, const std::vector<size_t>& ids);

#if 0
		void spliceTasks(TaskStatType from, TaskStatType to, Task** pTask, size_t num);
		//移动所有任务
		void spliceTasks(TaskStatType from, TaskStatType to);
#endif
	};
}
DefLog(hThread::hTaskMgr, _base, _tasks, _weights, _states);