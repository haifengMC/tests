#pragma once
#include "hSingleton.h"

namespace hThread
{
	class hPool : public Singleton<hPool>
	{
		bool _valid;
		size_t busyThd;
		std::vector<hTaskMgr> _taskMgr;

		ThreadPoolCfg cfgData;
	public:
		hPool();
		void init();
		void final();
		void run();
		void stop();

	};
}