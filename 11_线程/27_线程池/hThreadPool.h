#pragma once
#include "hSingleton.h"

namespace hThread
{
	struct ThreadMemMgr
	{
		//std::set<size_t> busyThd;
		std::set<size_t> _readyThd;//所有准备就绪的线程id
		std::vector<hTool::hAutoPtr<ThreadMem>> _memMgr;
	};

	class ThreadPool : public Singleton<ThreadPool>
	{
		DefLog_Init();
		friend class ThreadMem;
		//friend class Task;

		bool _valid;
		const ThreadBaseCfg& _base;

		//线程管理数组
		ThreadMemMgr _memMgrArr[ThreadMemType::Max];

		//size_t waitTask = 0;//等待任务数
		std::vector<hTool::hAutoPtr<TaskMgr>> _taskMgr;
		//std::map<Task*, hRWLock*> taskLock;//任务锁
	
		//hRWLock rwLock;//自锁
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
#endif
		void createThrd(size_t num, ThreadMemType t = ThreadMemType::Work);
#if 0
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
DefLog(hThread::ThreadMemMgr, _readyThd);
DefLog(hThread::ThreadPool, _valid, _base, _taskMgr);