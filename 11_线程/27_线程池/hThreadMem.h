#pragma once

namespace hThread
{
	ThreadMem* createThrdMem(ThreadMemType, size_t);

	class ThreadMem
	{
		DefLog_Init();
		PThread _pThrd;
		ThreadMemStatType _statType;
	protected:
		ThreadMemType _type = ThreadMemType::Max;

		size_t _id = 0;
		std::list<size_t>::iterator _statIt;//_thrdId中指向自己的迭代器
	
		std::function<void()> _func;
		//运行条件
		std::condition_variable _runCv;

		bool _close = false;//关闭标识符
	protected:
		virtual void setFunc() = 0;//设置线程每个线程成员都必须实现
	public:
		ThreadMem(size_t id);
		virtual ~ThreadMem() {}

		ThreadMemType getType() const { return _type; }
		ThreadMemStatType getStat() const { return _statType; }
		size_t getId() const { return _id; }

		void run();
		void stop();
		void join();

		bool setStat(ThreadMemStatType type, std::list<size_t>::iterator& it);
		bool updateStat(ThreadMemStatType type);
		void notify() { _runCv.notify_all(); }

		bool shouldBeClosed() const { return _close; }
		void close() { _close = true; }
	};

	//工作线程成员
	class ThreadMemWork : public ThreadMem
	{
		PWTask _pTask;//指向当前执行任务
		NodeListIt _nodeIt;//指向本线程运行的节点
		ThrdMemWorkListIt _memIt;//任务线程链表中自己的迭代器
		hRWLock* _pRwLock;//任务锁(由线程池提供)
	protected:
		void reset();
		void setFunc();
	public:
		ThreadMemWork(size_t id);
		~ThreadMemWork();

		void initTask(PWTask pTask, NodeListIt nodeIt, ThrdMemWorkListIt memIt);
		void runTask();

	};

	//管理线程成员
	class ThreadMemMgr : public ThreadMem
	{
	protected:
		void setFunc();
	public:
		ThreadMemMgr(size_t id);
		~ThreadMemMgr();
	};
}
DefLog(hThread::ThreadMem, _id);