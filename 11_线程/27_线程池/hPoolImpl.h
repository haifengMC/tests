#pragma once

namespace hThread
{
	template <size_t N>
	size_t hPool::commitTasks(PhTask(&task)[N], TaskMgrPriority priority)
	{
		if (TaskMgrPriority::Max <= priority)
			return 0;

		return _taskMgr[priority]->commitTasks(task);
	}
}