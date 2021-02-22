#pragma once
#include "hTool.h"

namespace hThread
{
	class TaskMgr : public hTool::hAutoPtrObj
	{
		DefLog_Init();
		friend class Task;

		const TaskMgrCfgItem& _base;

		hTool::hUniqueIdGen<size_t, Task> _tasks;//<id-Task>id生成器
		hTool::hRWeightMap<size_t> _weights;//权重管理<task thisId>
		std::list<size_t> _states[TaskStatType::Max];//状态管理<thisId>
	public:
		TaskMgr(const TaskMgrCfgItem& base);
		~TaskMgr();

		std::list<size_t>* getStateList(TaskStatType state);

		//提交任务，将新任务提交给管理器，提交后默认状态为等待
		template <size_t N>
		size_t commitTasks(PTask(&task)[N]);
		size_t commitTasks(PTask* task, size_t num);
		size_t commitTasks(PTask& task);
		//准备任务，按权重取出等待任务放入就绪任务，返回任务指针
		PTask readyTasks(size_t busy);
		//更新任务数据
		void updateTaskData(size_t taskId, byte opt, void* data);
#if 0

		//取消已准备任务,将就绪任务放回等待状态
		void cancelReadyTasks();
		//执行任务，就绪任务，返回实际执行的任务,numThr可用线程数
		size_t runTasks(size_t numThr, size_t rate);
#endif
	private:
		void spliceTasks(TaskStatType from, TaskStatType to, const std::vector<size_t>& ids);

#if 0
		void spliceTasks(TaskStatType from, TaskStatType to, Task** pTask, size_t num);
		//移动所有任务
		void spliceTasks(TaskStatType from, TaskStatType to);
#endif
	};
}
DefLog(hThread::TaskMgr, _base, _tasks, _weights, _states);