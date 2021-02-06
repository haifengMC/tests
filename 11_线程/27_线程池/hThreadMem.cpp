#include "global.h"
#include "hThread.h"
#include "hThreadPoolMgr.h"

namespace hThread
{
	ThreadMem* createThrdMem(ThreadMemType t, size_t id)
	{
		switch (t)
		{
		case ThreadMemType::Work:
			return new ThreadMemWork(id);
		case ThreadMemType::Mgr:
			return new ThreadMemMgr(id);
		default:
			break;
		}

		return NULL;
	}

	ThreadMem::ThreadMem(size_t id) : _id(id) {}

	void ThreadMem::run()
	{
		if (!updateStat(ThreadMemStatType::Wait))
			return;

		setFunc();
		_pThrd.bind(new std::thread(_func));
		//_pThrd->detach();
	}

	void ThreadMem::stop()
	{
		if (!updateStat(ThreadMemStatType::Init))
			return;

		close();
		notify();
	}

	void ThreadMem::join()
	{
		_pThrd->join();
	}

	bool ThreadMem::setStat(ThreadMemStatType type, std::list<size_t>::iterator& it)
	{
		if (_statType == type)
			return false;

		if (ThreadMemStatType::Max <= type)
			return false;

		_statType = type;
		_statIt = it;
		return true;
	}

	bool ThreadMem::updateStat(ThreadMemStatType type)
	{
		if (_statType == type)
			return false;

		if (ThreadMemStatType::Max <= type)
			return false;

		auto& data = sThrdPool.getThrdMemData(_type);
		auto& oldList = data._thrdId[_statType];
		auto& newList = data._thrdId[type];

		_statType = type;
		newList.splice(newList.end(), oldList, _statIt);
		return true;
	}

#if 0
	void ThreadMem::runTask(Task* const& task)
	{
		WT_LOCK;
		pTask = task;
		task->addThrd(this);
		WT_UNLOCK;
		runCv.notify_one();//Ӧ��Ϊ���̴߳���������������ǰ�򿪣�������Ӧ�������������������
	}
#endif
	void ThreadMemWork::setFunc()
	{
		_func = [&]()
		{
			COUT_LK(_id << " �����߳�����...");

			std::mutex m;
			std::unique_lock<std::mutex> lk(m);

			while (!_close)
			{
				//TaskNode* pNode = NULL;
				COUT_LK(_id << " �����߳̽���ѭ��...");

				_runCv.wait(lk, [&]
					{
						if (_close)
							return true;

						if (!_pTask)
						{
							COUT_LK(_id << " �����񣬹����̹߳���...");
							return false;
						}
#if 0

						if (!pTask || !pNext || !pRwLock || !pTask->getStat())
							return false;

						pRwLock->readLock();
						bool isFailed = TaskStateType::Error == pTask->getStat()->state;
						pRwLock->readUnlock();

						pRwLock->writeLock();
						pNode = pTask->getNextNode();
						pRwLock->writeUnlock();

						if (!pNode)//��ȡ�ڵ�ʧ��
							isFailed = true;

						if (isFailed)//����ʧЧ�ͷ��ڴ�
						{
							pRwLock->writeLock();
							pTask->setStat(TaskStateType::Error);
							pTask = NULL;
							pNext = NULL;
							pRwLock->writeUnlock();
							return false;
						}

#endif
						return true;
					});
				if (_close)
					break;
#if 0
				while (pNode)
				{
					if (!pNode->initProc())
					{
						pRwLock->writeLock();
						pTask->setStat(TaskStateType::Error);
						pTask = NULL;
						pNext = NULL;
						pRwLock->writeUnlock();
						break;
					}

					pRwLock->readLock();
					bool preRet = pNode->preProc();
					pRwLock->readUnlock();

					if (!preRet)//Ԥ����ʧ�ܣ�����������
					{
						pNode->finalProc();
						break;
					}

					runCv.wait(lk, [&]//�ȴ�
						{
							pRwLock->readLock();
							bool canProcV = pNode->canProc(nodeId);
							pRwLock->readUnlock();

							return canProcV;
						});

					pRwLock->writeLock();

					TaskNode* pCurNode = pNode;
					pNode = pTask->getNextNode();
					if (pNode)
						nodeId = pNode->getId();
					pCurNode->onProc();

					pRwLock->writeUnlock();

					pCurNode->finalProc();
					this->pNext->notify();
				}
#endif
			}
			//std::this_thread::sleep_for(std::chrono::seconds(1));
			COUT_LK(_id << " �����߳�ֹͣ����...");
		};
	}

	ThreadMemWork::ThreadMemWork(size_t id) :
		ThreadMem(id)
	{
		_type = ThreadMemType::Work;
		COUT_LK(_id << " �����̴߳���...");
	}

	ThreadMemWork::~ThreadMemWork() 
	{
		COUT_LK(_id << " �����߳��ͷ�...");
	}

	void ThreadMemWork::initTask(PWTask pTask, NodeListIt nodeIt, ThrdMemWorkListIt memIt)
	{
		COUT_LK(_id << " �����̳߳�ʼ������,id:" << pTask->getIndex() << "...");
		_pTask = pTask;
		_nodeIt = nodeIt;
		_memIt = memIt;
		setStat(ThreadMemStatType::Ready, _statIt);
	}

	void ThreadMemMgr::setFunc()
	{
		_func = [&]()
		{
			COUT_LK(_id << " �����߳�����...");

			std::mutex m;
			std::unique_lock<std::mutex> lk(m);

			while (!_close)
			{
				COUT_LK(_id << " �����߳̽���ѭ��...");

				PTask pTask;
				size_t thrdNum = 0;//�Ѿ����Ĺ����߳���
				_runCv.wait(lk, [&]
					{
						if (_close)
							return true;

						thrdNum = sThrdPool.getThrdMemNum(ThreadMemType::Work, ThreadMemStatType::Wait);
						if (!thrdNum)
						{
							COUT_LK(_id << " �޿����̣߳������̹߳���...");
							return false;
						}

						pTask = sThrdPool.readyTasks();
						if (!pTask)
						{
							COUT_LK(_id << " �����񣬹����̹߳���...");
							return false;
						}

						return true;
					});
				if (_close)
					break;

				COUT_LK(_id << " �����̳߳�ʼ������,id:" << pTask->getId() << "...");
				if (!sThrdPool.initTasks(pTask, thrdNum))
					continue;
		
				COUT_LK(_id << " �����߳�֪ͨ�����߳�ִ������,id:" << pTask->getId() << "...");
			}
			//std::this_thread::sleep_for(std::chrono::seconds(2));
			COUT_LK(_id << " �����߳�ֹͣ����...");
		};
	}

	ThreadMemMgr::ThreadMemMgr(size_t id) :
		ThreadMem(id)
	{
		_type = ThreadMemType::Mgr;
		COUT_LK(_id << " �����̴߳���...");
	}

	ThreadMemMgr::~ThreadMemMgr() 
	{ 
		COUT_LK(_id << " �����߳��ͷ�..."); 
	}
}

