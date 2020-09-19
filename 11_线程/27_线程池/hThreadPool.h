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

		size_t nodeId = 0;//��ǰִ�нڵ�id
		Task* pTask = NULL;
		ThreadMem* pNext = NULL;//�¸������߳�
		std::list<ThreadMem*>::iterator itMem;//�������߳��������Լ��ĵ�����
		hRWLock* pRwLock = NULL;//������(���̳߳��ṩ)

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
		std::vector<ThreadMem*> memMgr;//�̹߳���

		size_t waitTask = 0;//�ȴ�������
		std::vector<TaskMgr> taskMgr;
		std::map<Task*, hRWLock*> taskLock;//������
	
		hRWLock rwLock;//����
	public:
		operator bool() { return _invalid; }

		ThreadPool();
		~ThreadPool();
		void init();
		void final();
		void run();
		void stop();

		//�ύ����
		bool commitTasks(Task** const& task, const size_t& num = 1, TaskMgrPriority priority = TaskMgrPriority::Normal);
		hRWLock* getRWLock(Task* pTask);//��ȡ������

		void createThrd(const size_t& num);
		void closeThrd(const size_t& id);

		//����
		void readLock() { rwLock.readLock(); }
		void readUnlock() { rwLock.readUnlock(); }
		void writeLock() { rwLock.writeLock(); }
		void writeUnlock() { rwLock.writeUnlock(); }
	private:
		void runThrd(const size_t& num);//ʹ����num���������߳��Ϲ���
		void removeThrd(const size_t& id);
	};
#define sThreadPool hThread::ThreadPool::getMe()
}