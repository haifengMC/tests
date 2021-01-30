#pragma once
#include "hSingleton.h"

namespace hThread
{
	class ThreadPool;
	class Task;
	class ThreadMem
	{
		DefLog_Init();
		friend class Task;

		size_t _id = 0;
		std::function<void()> _func;
		std::thread _thrd;

#if 0

		std::condition_variable runCv;


		size_t nodeId = 0;//当前执行节点id
		Task* pTask = NULL;
		ThreadMem* pNext = NULL;//下个处理线程
		std::list<ThreadMem*>::iterator itMem;//任务中线程链表中自己的迭代器
		hRWLock* pRwLock = NULL;//任务锁(由线程池提供)

		bool shouldBeClosed = false;
#endif

	public:
		ThreadMem(size_t id);
		~ThreadMem();
#if 0

		void notify() { runCv.notify_all(); }

		void runTask(Task* const& task);

		const size_t& getId() const { return _id; }
		void setId(const size_t& id) { this->_id = id; }

		const bool& isClose() const { return shouldBeClosed; }
		void close() { shouldBeClosed = true; }
#endif
	};
	class ThreadPool : public Singleton<ThreadPool>
	{
		DefLog_Init();
		friend class ThreadMem;
		//friend class Task;

		bool _valid;
		const ThreadBaseCfg& _base;

		//std::set<size_t> busyThd;
		//std::set<size_t> readyThd;
		//std::vector<ThreadMem*> memMgr;//线程管理

		//size_t waitTask = 0;//等待任务数
		std::vector< hTool::hAutoPtr<TaskMgr>> _taskMgr;
		//std::map<Task*, hRWLock*> taskLock;//任务锁
	
		//hRWLock rwLock;//自锁
		std::mutex coutM;//输出互斥锁
	public:
		operator bool() { return _valid; }

		ThreadPool();
		~ThreadPool();

		void init();
		void final();
#if 0
		void run();
		void stop();
#endif
		//提交任务
		template <size_t N>
		size_t commitTasks(Task(&task)[N], TaskMgrPriority priority = TaskMgrPriority::Normal);
		size_t commitTasks(Task& task, TaskMgrPriority priority = TaskMgrPriority::Normal);
#if 0
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
#endif
	};
#define sThrdPool hThread::ThreadPool::getMe()
}
DefLog(hThread::ThreadMem, _id);
DefLog(hThread::ThreadPool, _valid, _base, _taskMgr);