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

	ThreadMem::~ThreadMem()
	{
		COUT_LK(_id << " 线程释放...");
	}

	void ThreadMem::run()
	{
		if (!updateStat(ThreadMemStatType::Ready))
			return;

		setFunc();
		_pThrd.bind(new std::thread(_func));
		_pThrd->detach();
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

		auto& data = sThrdPool.getMemData(_type);
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
		runCv.notify_one();//应当为本线程打开自锁，在任务锁前打开，任务锁应在添加完任务后由任务打开
	}
#endif
	void ThreadMemWork::setFunc()
	{
		_func = [&]()
		{
			COUT_LK(_id << " 工作线程启动...");

			std::mutex m;
			std::unique_lock<std::mutex> lk(m);

			while (!_close)
			{
				//TaskNode* pNode = NULL;
				COUT_LK(_id << " 工作线程进入循环...");

				_runCv.wait(lk, [&]
					{
						if (!_pTask)
						{
							COUT_LK(_id << " 无任务，工作线程挂起...");
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

						if (!pNode)//获取节点失败
							isFailed = true;

						if (isFailed)//任务失效释放内存
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

					if (!preRet)//预处理失败，做后续处理
					{
						pNode->finalProc();
						break;
					}

					runCv.wait(lk, [&]//等待
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
			//sThreadPool.removeThrd(id);
		};
	}

	ThreadMemWork::ThreadMemWork(size_t id) :
		ThreadMem(id)
	{
		_type = ThreadMemType::Work;
		COUT_LK(_id << " 工作线程创建...");
	}

	void ThreadMemMgr::setFunc()
	{
		_func = [&]()
		{
			COUT_LK(_id << " 管理线程启动...");

			std::mutex m;
			std::unique_lock<std::mutex> lk(m);

			while (!_close)
			{
				COUT_LK(_id << " 管理线程进入循环...");

				_runCv.wait(lk, [&]
					{


						COUT_LK(_id << " 管理线程挂起...");
						return false;
					});
			}
		};
	}

	ThreadMemMgr::ThreadMemMgr(size_t id) :
		ThreadMem(id)
	{
		_type = ThreadMemType::Mgr;
		COUT_LK(_id << " 管理线程创建...");
	}
}