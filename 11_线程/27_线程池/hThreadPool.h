#pragma once
#include "hSingleton.h"

namespace hThread
{
	class TreadPool : public Singleton<TreadPool>
	{
		bool _invalid;
		const TreadBaseCfg& base;

		size_t busyThd;
		std::vector<TaskMgr> taskMgrs;
	public:
		operator bool() { return _invalid; }

		TreadPool();
		void init();
		void final();
		void run();
		void stop();

	};
#define sTreadPool hThread::TreadPool::getMe()
}