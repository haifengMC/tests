#include "global.h"
#include "hThread.h"
#include "hThreadPoolMgr.h"

namespace hThread
{
	void ThreadMemFunc::operator() ()
	{
		for (size_t i = 0; i < 5; ++i)
		{
			this_thread::sleep_for(std::chrono::seconds(1));
			//std::cout << id << ":" 
		}

	}


	ThreadPool::ThreadPool() : 
		_invalid(sTreadPoolMgr), base(sTreadPoolMgr.getBaseCfg()),
		busyThd(0) { init(); }

	ThreadPool::~ThreadPool() { final(); }

	void ThreadPool::init()
	{
		if (_invalid)
		{//Err
			return;
		}
		for (auto& item : sTreadPoolMgr.getTaskMgrCfg())
			taskMgr.emplace_back(item.second);

		for (size_t i = 0; i < base.initThd; ++i)
			memMgr.push_back(new ThreadMem(i, *this));
	}

	void ThreadPool::final()
	{
		for (auto& pMem : memMgr)
			DEL(pMem);
	}

	void ThreadPool::run()
	{
	}

	void ThreadPool::stop()
	{
	}
}