#pragma once
#include "hSingleton.h"

namespace hThread
{
	class hPool : public Singleton<hPool>
	{
		DefLog_Init();
		friend class hMemBase;
		friend class hTaskBase;

		bool _valid;
		const ThreadBaseCfg& _base;

		//�̹߳���������
		hMemData _memData[ThreadMemType::Max];

		//size_t waitTask = 0;//�ȴ�������
		PhTaskMgr _taskMgr[TaskMgrPriority::Max];
		//std::map<Task*, hRWLock*> taskLock;//������
	
		//hRWLock rwLock;//����
	public:
		operator bool() { return _valid; }
		
		hPool();
		~hPool();
		
		void init();
		void final();
		void run();
		void stop();
		
		//�ύ����
		template <size_t N>
		size_t commitTasks(PhTask(&task)[N], TaskMgrPriority priority = TaskMgrPriority::Normal);
		size_t commitTasks(PhTask& task, TaskMgrPriority priority = TaskMgrPriority::Normal);
		//׼������:�����̸߳������ȼ���Ȩ��
		PhTask readyTasks();
		//��ʼ������:�����߳�Ϊ�����̳߳�ʼ������״̬
		bool initTasks(PhTask pTask, size_t thrdNum);
		//��������:֪ͨ�������Ĺ����̹߳���
		void runTasks();

		void createThrd(size_t num, ThreadMemType t = ThreadMemType::Work);
		hMemData& getThrdMemData(ThreadMemType type) { return _memData[type]; }
		size_t getThrdMemNum(ThreadMemType memTy, ThreadMemStatType statTy);
		//֪ͨ�����߳�����
		void notifyMgrThrd();
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
#define shPool hThread::hPool::getMe()
#define shPoolFin hThread::hPool::delMe()
}
DefLog(hThread::hPool, _valid, _base, _memData, _taskMgr);