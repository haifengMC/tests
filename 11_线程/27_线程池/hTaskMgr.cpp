#include "global.h"
#include "hTool.h"
#include "hThread.h"

namespace hThread
{
	TaskMgr::TaskMgr(const TaskMgrCfgItem& base) : base(base) {}

	bool TaskMgr::TasksData::popTask(Task*& task)
	{
		if (weightTasks.empty())
			return false;

		size_t randWeight[1] = {};
		if (!RANDOM(hTool::RandomType::UniformInt, randWeight, 0, totalWeight))
			return false;

		size_t tmpWeight = 0;
		for (auto it = weightTasks.begin(); it != weightTasks.end();)
		{
			if (it->second.empty())
			{
				it = weightTasks.erase(it);
				continue;
			}

			std::pair<const size_t, std::vector<Task*>>& tasks = *(it++);
			size_t addWeight = tasks.first * tasks.second.size();
			if (tmpWeight + addWeight < randWeight[0])
			{
				tmpWeight += addWeight;
				continue;
			}
			size_t idx = (randWeight[0] - tmpWeight) / tasks.first;
			task = tasks.second[idx];
			idTasks.erase(task->getId());
			tasks.second[idx] = *tasks.second.rbegin();
			tasks.second.pop_back();

			if (tasks.second.empty())
				weightTasks.erase(tasks.first);

			return true;
		}

		return false;
	}

	size_t TaskMgr::popTasks(Task** pTask, const size_t& num)
	{
		size_t ret = 0;
		for (; ret < num; ++ret)
			if (!allTasks.popTask(pTask[ret]))
				break;

		return ret;
	}
}