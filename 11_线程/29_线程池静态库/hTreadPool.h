#pragma once
#include "hSingleton.h"

namespace hThread
{
	class TreadPool : public Singleton<TreadPool>
	{
		bool _invalid;
		size_t busyThd;
		std::vector<TaskMgr> taskMgrs;

		ThreadPoolCfg cfgData;
	public:
		TreadPool();
		void init();
		void final();
		void run();
		void stop();

	};
}