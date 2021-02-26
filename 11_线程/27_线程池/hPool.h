#pragma once
#include "hSingleton.h"

namespace hThread
{
	class hPool : public Singleton<hPool>
	{
		DefLog_Init();
		friend class hMem;
		friend class hTask;

		bool _valid;
		const ThreadBaseCfg& _base;

		//线程管理组数据
		hMemData _memData[ThreadMemType::Max];

		//size_t waitTask = 0;//等待任务数
		std::vector<PhTaskMgr> _taskMgr;
		//std::map<Task*, hRWLock*> taskLock;//任务锁
	
		//hRWLock rwLock;//自锁
	public:
		operator bool() { return _valid; }
		
		hPool();
		~hPool();
		
		void init();
		void final();
		void run();
		void stop();
		
		//提交任务
		template <size_t N>
		size_t commitTasks(PhTask(&task)[N], TaskMgrPriority priority = TaskMgrPriority::Normal);
		size_t commitTasks(PhTask& task, TaskMgrPriority priority = TaskMgrPriority::Normal);
		//准备任务:管理线程根据优先级和权重
		PhTask readyTasks();
		//初始化任务:管理线程为工作线程初始化任务状态
		bool initTasks(PhTask pTask, size_t thrdNum);
		//运行任务:通知各就绪的工作线程工作
		void runTasks();

		void createThrd(size_t num, ThreadMemType t = ThreadMemType::Work);
		hMemData& getThrdMemData(ThreadMemType type) { return _memData[type]; }
		size_t getThrdMemNum(ThreadMemType memTy, ThreadMemStatType statTy);
		//通知管理线程运行
		void notifyMgrThrd();
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
#define shPool hThread::hPool::getMe()
#define shPoolFin hThread::hPool::delMe()
}
DefLog(hThread::hPool, _valid, _base, _memData, _taskMgr);