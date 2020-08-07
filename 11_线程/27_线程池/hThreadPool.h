#pragma once
#include "hSingleton.h"

namespace hThread
{
	class ThreadPool;
	class ThreadMem;
	class ThreadMemFunc
	{
		friend class ThreadMem;

		const size_t& id;
		Task*& pTask;
		std::condition_variable& runCv;//运行条件

	public:
		ThreadMemFunc(const size_t& id, Task*& pTask, std::condition_variable& runCv) :
			id(id), pTask(pTask), runCv(runCv) {}
		void operator()();

		const bool& isClose() const;
	};

	class Task;
	class ThreadMem
	{
		size_t id = 0;
		std::condition_variable runCv;
		ThreadMemFunc func; 

		std::thread thrd;

		Task* pTask = NULL;
		bool shouldBeClosed = false;

	public:
		ThreadMem(const size_t& id);

		void runTask(Task* const& task);

		const size_t& getId() const { return id; }
		void setId(const size_t& id) { this->id = id; }

		const bool& isClose() const { return shouldBeClosed; }
		void close() { shouldBeClosed = true; }
	};

	class ThreadPool : public Singleton<ThreadPool>
	{
		friend class ThreadMemFunc;
		friend class Task;

		bool _invalid;
		const TreadBaseCfg& base;

		std::set<size_t> busyThd;
		std::set<size_t> readyThd;
		std::vector<ThreadMem*> memMgr;//线程管理

		size_t waitTask = 0;//等待任务数
		std::vector<TaskMgr> taskMgr;

		hRWLock rwLock;//自锁
	public:
		operator bool() { return _invalid; }

		ThreadPool();
		~ThreadPool();
		void init();
		void final();
		void run();
		void stop();

		void createThrd(const size_t& num);
		void closeThrd(const size_t& id);

		void readLock() { rwLock.readLock(); }
		void readUnlock() { rwLock.readUnlock(); }
		void writeLock() { rwLock.writeLock(); }
		void writeUnlock() { rwLock.writeUnlock(); }
	private:
		void runThrd(const size_t& num);
		void removeThrd(const size_t& id);

		size_t runTasks(Task** &pTasks, const size_t& num, const size_t& rate);
	};
#define sThreadPool hThread::ThreadPool::getMe()
}