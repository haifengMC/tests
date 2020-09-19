#pragma once
#include "hTool.h"

namespace hThread
{
	class TaskMgr
	{
		const TaskMgrCfgItem& base;

		std::map <size_t, Task> tasks;//<id-Task>

		hTool::hUniqueIdGen<size_t, Task> tasksIdGen;//id生成器
		hTool::hRWeightMap<Task*> weights;//权重管理
		std::list<Task*> states[TaskStateType::Max];//状态管理
	public:
		TaskMgr(const TaskMgrCfgItem& base);

		//提交任务，将新任务提交给管理器，提交后默认状态为等待
		size_t commitTasks(Task* task, size_t num);
		//准备任务，按权重取出等待任务放入就绪任务，返回取出数量
		size_t readyTasks(size_t num, size_t busy);
		//取消已准备任务,将就绪任务放回等待状态
		void cancelReadyTasks();
		size_t runTasks(size_t numThr, size_t rate);
		size_t pushTasks(Task** const& task, const size_t& num);
		size_t popTasks(Task** task, size_t begNum, size_t num, size_t busy);
	private:
		void spliceTasks(TaskStateType from, TaskStateType to, Task** pTask, size_t num);
		void spliceTasks(TaskStateType from, TaskStateType to, const std::vector<Task*>& tDataVec);
		//移动所有任务
		void spliceTasks(TaskStateType from, TaskStateType to);
	};
}