#pragma once

namespace hThread
{
	template <size_t N>
	size_t hTaskMgrBase::commitTasks(PhTask(&task)[N])
	{
		if (!N) return 0;
		return commitTasks(task, N);
	}
}
