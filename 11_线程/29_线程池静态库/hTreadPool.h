#pragma once
#include "hSingleton.h"

namespace hThread
{
	class ThreadPool : public Singleton<ThreadPool>
	{
		bool _valid;
		size_t busyThd;
		std::vector<TaskMgr> _taskMgr;

		ThreadPoolCfg cfgData;
	public:
		ThreadPool();
		void init();
		void final();
		void run();
		void stop();

	};
}