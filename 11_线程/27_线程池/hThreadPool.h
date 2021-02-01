#pragma once
#include "hSingleton.h"

namespace hThread
{
	struct ThreadMemData
	{
		ThreadMemType _type = ThreadMemType::Max;
		//����״̬���߳�id
		std::list<size_t> _thrdId[ThreadMemStatType::Max];
		std::vector<hTool::hAutoPtr<ThreadMem>> _memArr;

		void init(size_t num);
		void run();
	};

	class ThreadPool : public Singleton<ThreadPool>
	{
		DefLog_Init();
		friend class ThreadMem;
		//friend class Task;

		bool _valid;
		const ThreadBaseCfg& _base;

		//�̹߳���������
		ThreadMemData _memData[ThreadMemType::Max];

		//size_t waitTask = 0;//�ȴ�������
		std::vector<hTool::hAutoPtr<TaskMgr>> _taskMgr;
		//std::map<Task*, hRWLock*> taskLock;//������
	
		//hRWLock rwLock;//����
	public:
		operator bool() { return _valid; }

		ThreadPool();
		~ThreadPool();

		void init();
		void final();
		void run();
#if 0
		void stop();
#endif
		//�ύ����
		template <size_t N>
		size_t commitTasks(Task(&task)[N], TaskMgrPriority priority = TaskMgrPriority::Normal);
		size_t commitTasks(Task& task, TaskMgrPriority priority = TaskMgrPriority::Normal);
		//ѡ�����񣺸������ȼ���Ȩ��

#if 0
		hRWLock* getRWLock(Task* pTask);//��ȡ������
#endif
		void createThrd(size_t num, ThreadMemType t = ThreadMemType::Work);
		ThreadMemData& getMemData(ThreadMemType type) { return _memData[type]; }
#if 0
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
DefLog(hThread::ThreadMemData, _thrdId);
DefLog(hThread::ThreadPool, _valid, _base, _memData, _taskMgr);