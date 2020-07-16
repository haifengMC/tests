#pragma once
#include "hSingleton.h"

namespace hThread
{
	class ThreadPool;
	class ThreadMemFunc
	{
		ThreadPool& pool;

	public:
		ThreadMemFunc(ThreadPool& pool) : pool(pool) {}
		void operator()();
	};

	class ThreadMem
	{
		size_t id;
		ThreadMemFunc func;

		bool shouldBeClosed = false;
		std::thread thrd;

	public:
		ThreadMem(const size_t& id, ThreadPool& pool) :
			id(id), func(pool), thrd(func) { thrd.detach(); }

		bool isClose() const { return shouldBeClosed; }
	};

	class ThreadPool : public Singleton<ThreadPool>
	{
		bool _invalid;
		const TreadBaseCfg& base;

		size_t busyThd;
		std::vector<ThreadMem*> memMgr;//线程管理

		std::vector<TaskMgr> taskMgr;
	public:
		operator bool() { return _invalid; }

		ThreadPool();
		~ThreadPool();
		void init();
		void final();
		void run();
		void stop();

	};
#define sThreadPool hThread::ThreadPool::getMe()
}