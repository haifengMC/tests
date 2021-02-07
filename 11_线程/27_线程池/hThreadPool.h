#pragma once
#include "hSingleton.h"

namespace hThread
{
	struct ThreadMemData
	{
		ThreadMemType _type = ThreadMemType::Max;
		//����״̬���߳�id
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
		friend class Task;

		bool _valid;
		const ThreadBaseCfg& _base;

		//�̹߳���������
		ThreadMemData _memData[ThreadMemType::Max];

		//size_t waitTask = 0;//�ȴ�������
		std::vector<PTaskMgr> _taskMgr;
		//std::map<Task*, hRWLock*> taskLock;//������
	
		//hRWLock rwLock;//����
	public:
		operator bool() { return _valid; }
		
		ThreadPool();
		~ThreadPool();
		
		void init();
		void final();
		void run();
		void stop();
		
		//�ύ����
		template <size_t N>
		size_t commitTasks(PTask(&task)[N], TaskMgrPriority priority = TaskMgrPriority::Normal);
		size_t commitTasks(PTask& task, TaskMgrPriority priority = TaskMgrPriority::Normal);
		//׼������:�����̸߳������ȼ���Ȩ��
		PTask readyTasks();
		//��ʼ������:�����߳�Ϊ�����̳߳�ʼ������״̬
		bool initTasks(PTask pTask, size_t thrdNum);
		//��������:֪ͨ�������Ĺ����̹߳���
		void runTasks();

		void createThrd(size_t num, ThreadMemType t = ThreadMemType::Work);
		ThreadMemData& getThrdMemData(ThreadMemType type) { return _memData[type]; }
		size_t getThrdMemNum(ThreadMemType memTy, ThreadMemStatType statTy);
#if 0
		void closeThrd(const size_t& id);

		//����
		void readLock() { rwLock.readLock(); }
		void readUnlock() { rwLock.readUnlock(); }
		void writeLock() { rwLock.writeLock(); }
		void writeUnlock() { rwLock.writeUnlock(); }

	private:
		void runThrd(const size_t& num);//ʹ����num���������߳��Ϲ���
		size_t getThrdMemNum(ThreadMemType memTy, ThreadMemStatType statTy);
		void removeThrd(const size_t& id);
#endif
	};
#define sThrdPool hThread::ThreadPool::getMe()
#define sThrdPoolFin hThread::ThreadPool::delMe()
}
DefLog(hThread::ThreadMemData, _thrdId);
DefLog(hThread::ThreadPool, _valid, _base, _memData, _taskMgr);