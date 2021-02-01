#pragma once

namespace hThread
{
	class ThreadMem;
	ThreadMem* createThrdMem(ThreadMemType, size_t);

	//class ThreadPool;
	class ThreadMem
	{
		DefLog_Init();
		hTool::hAutoPtr<std::thread> _pThrd;

		ThreadMemStatType _statType;
		std::list<size_t>::iterator _statIt;//_thrdId��ָ���Լ��ĵ�����
	protected:
		ThreadMemType _type = ThreadMemType::Max;
		size_t _id = 0;
		std::function<void()> _func;
		//��������
		std::condition_variable _runCv;

		bool _close = false;//�رձ�ʶ��

#if 0

		size_t nodeId = 0;//��ǰִ�нڵ�id
		Task* pTask = NULL;
		ThreadMem* pNext = NULL;//�¸������߳�
		std::list<ThreadMem*>::iterator itMem;//�������߳��������Լ��ĵ�����
		hRWLock* pRwLock = NULL;//������(���̳߳��ṩ)

#endif
	protected:
		virtual void setFunc() = 0;//�����߳�ÿ���̳߳�Ա������ʵ��
	public:
		ThreadMem(size_t id);
		virtual ~ThreadMem();

		void run();

		bool setStat(ThreadMemStatType type, std::list<size_t>::iterator& it);
		bool updateStat(ThreadMemStatType type);
#if 0

		void notify() { runCv.notify_all(); }

		void runTask(Task* const& task);

		const size_t& getId() const { return _id; }
		void setId(const size_t& id) { this->_id = id; }
#endif

		bool shouldBeClosed() const { return _close; }
		void close() { _close = true; }
	};

	//�����̳߳�Ա
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

	//�����̳߳�Ա
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