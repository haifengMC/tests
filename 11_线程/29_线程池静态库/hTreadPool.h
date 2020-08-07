#pragma once
#include "hSingleton.h"

namespace hThread
{
	class ThreadPool : public Singleton<ThreadPool>
	{
		bool _invalid;
		size_t busyThd;
		std::vector<TaskMgr> taskMgr;

		ThreadPoolCfg cfgData;
	public:
		ThreadPool();
		void init();
		void final();
		void run();
		void stop();

	};
}