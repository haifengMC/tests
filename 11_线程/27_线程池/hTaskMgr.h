#pragma once
#include "hTool.h"

namespace hThread
{
	class TaskMgr
	{
		DefLog_Init();
		friend class Task;

		const TaskMgrCfgItem& _base;

		std::map <size_t, Task> _tasks;//<id-Task>
		hTool::hUniqueIdGen<size_t, Task> _tasksIdGen;//id生成器
		hTool::hRWeightMap<size_t> _weights;//权重管理<task thisId>
		std::list<size_t> _states[TaskStatType::Max];//状态管理<thisId>
	public:
		TaskMgr(const TaskMgrCfgItem& base);

		//提交任务，将新任务提交给管理器，提交后默认状态为等待
		template <size_t N>
		size_t commitTasks(Task (&task)[N]);
		size_t commitTasks(Task& task);
		size_t commitTasks(Task* task, size_t num);
#if 0

		//准备任务，按权重取出等待任务放入就绪任务，返回取出数量
		size_t readyTasks(size_t num, size_t busy);
		//取消已准备任务,将就绪任务放回等待状态
		void cancelReadyTasks();
		//执行任务，就绪任务，返回实际执行的任务,numThr可用线程数
		size_t runTasks(size_t numThr, size_t rate);
#endif

#if 0
	private:
		void spliceTasks(TaskStateType from, TaskStateType to, Task** pTask, size_t num);
		void spliceTasks(TaskStateType from, TaskStateType to, const std::vector<Task*>& tDataVec);
		//移动所有任务
		void spliceTasks(TaskStateType from, TaskStateType to);
#endif
	};
}
DefLog(hThread::TaskMgr, _base, _tasks, _weights, _states);