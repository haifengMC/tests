#pragma once

namespace hThread
{
	template <size_t N>
	size_t TaskMgr::commitTasks(PTask(&task)[N])
	{
		if (!N) return 0;
		return commitTasks(task, N);
	}
}
