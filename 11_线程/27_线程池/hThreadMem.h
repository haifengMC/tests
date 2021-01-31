#pragma once

namespace hThread
{
	class ThreadMem;
	ThreadMem* createThrdMem(ThreadMemType, size_t);

	//class ThreadPool;
	class ThreadMem
	{
		DefLog_Init();
		std::thread _thrd;
	protected:
		size_t _id = 0;
		std::function<void()> _func;
		//运行条件
		std::condition_variable _runCv;

		bool _close = false;//关闭标识符

#if 0

		size_t nodeId = 0;//当前执行节点id
		Task* pTask = NULL;
		ThreadMem* pNext = NULL;//下个处理线程
		std::list<ThreadMem*>::iterator itMem;//任务中线程链表中自己的迭代器
		hRWLock* pRwLock = NULL;//任务锁(由线程池提供)

#endif
	private:

	protected:
		virtual void setFunc() = 0;//设置线程每个线程成员都必须实现
	public:
		ThreadMem(size_t id);
		virtual ~ThreadMem();

#if 0

		void notify() { runCv.notify_all(); }

		void runTask(Task* const& task);

		const size_t& getId() const { return _id; }
		void setId(const size_t& id) { this->_id = id; }
#endif

		bool shouldBeClosed() const { return _close; }
		void close() { _close = true; }
	};

	//工作线程成员
	class ThreadMemWork : public ThreadMem
	{
		friend class Task;
		hTool::hAutoPtr<Task> _pTask;
	protected:
		void setFunc();
	public:
		ThreadMemWork(size_t id);
		~ThreadMemWork() {}
	};
}
DefLog(hThread::ThreadMem, _id);