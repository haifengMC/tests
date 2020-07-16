#pragma once

namespace hThread
{
	template<size_t N>
	size_t TaskMgr::popTasks(Task* (&tasks)[N]) { return popTasks(tasks, N); }
}
