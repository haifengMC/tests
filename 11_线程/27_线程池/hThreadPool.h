#pragma once
#include "hSingleton.h"

namespace hThread
{
	struct ThreadMemData
	{
		ThreadMemType _type = ThreadMemType::Max;
		//所有状态的线程id
		std::list<size_t> _thrdId[ThreadMemStatType::Max];
		std::vector<PThrdMem> _memArr;

		void init(size_t num);
		void run();
		void stop();
		void join();

		void execEvery(ThreadMemStatType statTy, std::function<bool(PThrdMem)> func);
	};

	class ThreadPool : public Singleton<ThreadPool>
	{
		DefLog_Init();
		friend class ThreadMem;
		//friend class Task;

		bool _valid;
		const ThreadBaseCfg& _base;

		//线程管理组数据
		ThreadMemData _memData[ThreadMemType::Max];

		//size_t waitTask = 0;//等待任务数
		std::vector<PTaskMgr> _taskMgr;
		//std::map<Task*, hRWLock*> taskLock;//任务锁
	
		//hRWLock rwLock;//自锁
	public:
		operator bool() { return _valid; }

		ThreadPool();
		~ThreadPool();

		void init();
		void final();
		void run();
		void stop();

		//提交任务
		template <size_t N>
		size_t commitTasks(PTask(&task)[N], TaskMgrPriority priority = TaskMgrPriority::Normal);
		size_t commitTasks(PTask& task, TaskMgrPriority priority = TaskMgrPriority::Normal);
		//准备任务：管理线程根据优先级和权重
		PTask readyTasks();
		//初始化任务:管理线程为工作线程初始化任务状态
		bool initTasks(PTask pTask, size_t thrdNum);
#if 0
		hRWLock* getRWLock(Task* pTask);//获取任务锁
#endif
		void createThrd(size_t num, ThreadMemType t = ThreadMemType::Work);
		ThreadMemData& getThrdMemData(ThreadMemType type) { return _memData[type]; }
		size_t getThrdMemNum(ThreadMemType memTy, ThreadMemStatType statTy);
#if 0
		void closeThrd(const size_t& id);

		//自锁
		void readLock() { rwLock.readLock(); }
		void readUnlock() { rwLock.readUnlock(); }
		void writeLock() { rwLock.writeLock(); }
		void writeUnlock() { rwLock.writeUnlock(); }

	private:
		void runThrd(const size_t& num);//使至多num个任务在线程上工作
		size_t getThrdMemNum(ThreadMemType memTy, ThreadMemStatType statTy);
		void removeThrd(const size_t& id);
#endif
	};
#define sThrdPool hThread::ThreadPool::getMe()
}
DefLog(hThread::ThreadMemData, _thrdId);
DefLog(hThread::ThreadPool, _valid, _base, _memData, _taskMgr);