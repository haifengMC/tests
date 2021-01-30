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


		size_t nodeId = 0;//��ǰִ�нڵ�id
		Task* pTask = NULL;
		ThreadMem* pNext = NULL;//�¸������߳�
		std::list<ThreadMem*>::iterator itMem;//�������߳��������Լ��ĵ�����
		hRWLock* pRwLock = NULL;//������(���̳߳��ṩ)

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
		//std::vector<ThreadMem*> memMgr;//�̹߳���

		//size_t waitTask = 0;//�ȴ�������
		std::vector< hTool::hAutoPtr<TaskMgr>> _taskMgr;
		//std::map<Task*, hRWLock*> taskLock;//������
	
		//hRWLock rwLock;//����
		std::mutex coutM;//���������
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
		//�ύ����
		template <size_t N>
		size_t commitTasks(Task(&task)[N], TaskMgrPriority priority = TaskMgrPriority::Normal);
		size_t commitTasks(Task& task, TaskMgrPriority priority = TaskMgrPriority::Normal);
#if 0
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
#endif
	};
#define sThrdPool hThread::ThreadPool::getMe()
}
DefLog(hThread::ThreadMem, _id);
DefLog(hThread::ThreadPool, _valid, _base, _taskMgr);