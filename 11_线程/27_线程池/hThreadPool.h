#pragma once
#include "hSingleton.h"

namespace hThread
{
	class ThreadPool;
	class Task;
	class ThreadMem
	{
		friend class Task;

		size_t id = 0;
		std::condition_variable runCv;

		std::function<void()> func;
		std::thread thrd;

		size_t nodeId = 0;//当前执行节点id
		Task* pTask = NULL;
		ThreadMem* pNext = NULL;//下个处理线程
		std::list<ThreadMem*>::iterator itMem;//任务中线程链表中自己的迭代器
		hRWLock* pRwLock = NULL;//任务锁(由线程池提供)

		bool shouldBeClosed = false;

	public:
		ThreadMem(const size_t& id);
		~ThreadMem();

		void notify() { runCv.notify_all(); }

		void runTask(Task* const& task);

		const size_t& getId() const { return id; }
		void setId(const size_t& id) { this->id = id; }

		const bool& isClose() const { return shouldBeClosed; }
		void close() { shouldBeClosed = true; }
	};

	class ThreadPool : public Singleton<ThreadPool>
	{
		friend class ThreadMem;
		friend class Task;

		bool _invalid;
		const TreadBaseCfg& base;

		std::set<size_t> busyThd;
		std::set<size_t> readyThd;
		std::vector<ThreadMem*> memMgr;//线程管理

		size_t waitTask = 0;//等待任务数
		std::vector<TaskMgr> taskMgr;
		std::map<Task*, hRWLock*> taskLock;//任务锁
	
		hRWLock rwLock;//自锁
	public:
		operator bool() { return _invalid; }

		ThreadPool();
		~ThreadPool();
		void init();
		void final();
		void run();
		void stop();

		//提交任务
		bool commitTasks(Task** const& task, const size_t& num = 1, TaskMgrPriority priority = TaskMgrPriority::Normal);
		hRWLock* getRWLock(Task* pTask);//获取任务锁

		void createThrd(const size_t& num);
		void closeThrd(const size_t& id);

		//自锁
		void readLock() { rwLock.readLock(); }
		void readUnlock() { rwLock.readUnlock(); }
		void writeLock() { rwLock.writeLock(); }
		void writeUnlock() { rwLock.writeUnlock(); }
	private:
		void runThrd(const size_t& num);//使至多num个任务在线程上工作
		void removeThrd(const size_t& id);
	};
#define sThreadPool hThread::ThreadPool::getMe()
}