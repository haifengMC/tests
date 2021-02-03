#pragma once

namespace hThread
{
	ThreadMem* createThrdMem(ThreadMemType, size_t);

	class ThreadMem
	{
		DefLog_Init();
		hTool::hAutoPtr<std::thread> _pThrd;

		ThreadMemStatType _statType;
		std::list<size_t>::iterator _statIt;//_thrdId中指向自己的迭代器
	protected:
		ThreadMemType _type = ThreadMemType::Max;
		size_t _id = 0;
		std::function<void()> _func;
		//运行条件
		std::condition_variable _runCv;

		bool _close = false;//关闭标识符

#if 0

		hRWLock* pRwLock = NULL;//任务锁(由线程池提供)

#endif
	protected:
		virtual void setFunc() = 0;//设置线程每个线程成员都必须实现
	public:
		ThreadMem(size_t id);
		virtual ~ThreadMem();
		void destoryPtr() {}

		ThreadMemType getType() const { return _type; }
		ThreadMemStatType getStat() const { return _statType; }
		size_t getId() const { return _id; }

		void run();
		void stop();
		void join();

		bool setStat(ThreadMemStatType type, std::list<size_t>::iterator& it);
		bool updateStat(ThreadMemStatType type);
#if 0


		void runTask(Task* const& task);

		const size_t& getId() const { return _id; }
		void setId(const size_t& id) { this->_id = id; }
#endif
		void notify() { _runCv.notify_all(); }

		bool shouldBeClosed() const { return _close; }
		void close() { _close = true; }
	};

	//工作线程成员
	class ThreadMemWork : public ThreadMem
	{
		friend class Task;
		PTask _pTask;//指向当前执行任务
		NodeListIt _nodeIt;//指向本线程运行的节点
		ThrdMemListIt _memIt;//任务线程链表中自己的迭代器
	protected:
		void setFunc();
	public:
		ThreadMemWork(size_t id);
		~ThreadMemWork() {}

		void initTask(PTask pTask);
	};

	//管理线程成员
	class ThreadMemMgr : public ThreadMem
	{
	protected:
		void setFunc();
	public:
		ThreadMemMgr(size_t id);
		~ThreadMemMgr() {}
	};
}
DefLog(hThread::ThreadMem, _id);