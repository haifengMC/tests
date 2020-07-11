#pragma once

namespace hThread
{
	class TaskMgr
	{
		const TaskMgrCfgItem& base;

		std::map<size_t, Task> tasks;
		public:
			TaskMgr(const TaskMgrCfgItem& base);
	};
}