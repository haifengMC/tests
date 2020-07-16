#pragma once
#include "hTool.h"

namespace hThread
{
	class TaskMgr
	{
		const TaskMgrCfgItem& base;

		class TasksData
		{
			size_t totalWeight = 0;
			std::map<size_t, Task*> idTasks;//<id-task>
			std::map<size_t, std::vector<Task*>> weightTasks;//<weight-task>
		public:
			bool popTask(Task*& task);
		private:
		} allTasks;

	public:
		TaskMgr(const TaskMgrCfgItem& base);

		
		size_t popTasks(Task** pTask, const size_t& num);
		template<size_t N>
		size_t popTasks(Task* (&tasks)[N]);
	};
}