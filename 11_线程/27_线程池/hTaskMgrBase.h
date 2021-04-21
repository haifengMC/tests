#pragma once

namespace hThread
{
	class hTaskMgrBase : public hTool::hAutoPtrObj
	{
		DefLog_Init();
		hTaskMgr::PhCfgDt _pCfg;
		hTaskMgr::PhTskMgrDt _pTaskMgr;//<id-Task>id生成器
		hTaskMgr::PhWtMgrDt _pWeightMgr;//权重管理<task thisId>
		hTaskMgr::PhStatMgrDt _pStatMgr;//状态管理<thisId>
		hTaskMgr::PhUpMgrDt _pUpdateMgr;//数据更新 任务id
	public:
		void init(const TaskMgrCfgItem& base);
		const char* getName() const;

		//提交任务，将新任务提交给管理器，提交后默认状态为等待
		template <size_t N>
		size_t commitTasks(PhTask(&task)[N]);
		size_t commitTasks(PhTask* task, size_t num);
		size_t commitTasks(PhTask& task);
		//准备任务，按权重取出等待任务放入就绪任务，返回任务指针
		PhTask readyTasks(size_t busy);
		//更新任务状态
		bool updateTaskState(size_t tskId, std::list<size_t>::iterator statIt,
			TaskStatType oldStat, TaskStatType newStat);
		//更新任务数据
		template <typename ... Args >
		void updateTaskData(size_t taskId, size_t opt, Args ... args);
		//向更新任务添加函数
		void addUpdateTaskFunc(size_t taskId,
			std::function<bool()> checkFn,
			std::function<void()> execFn);

		//将任务加入权重管理
		void pushTask2Weight(PhTask pTask) { _pWeightMgr->pushTask(pTask); }
		void pushTask2Weight(PWhTask pTask) { _pWeightMgr->pushTask(pTask); }
		//将任务加入状态管理
		std::list<size_t>::iterator pushTask2Stat(PhTask pTask) { return _pStatMgr->pushTask(pTask); }
	};
}
DefLog(hThread::hTaskMgrBase, _pCfg, _pTaskMgr, _pWeightMgr, _pStatMgr, _pUpdateMgr);