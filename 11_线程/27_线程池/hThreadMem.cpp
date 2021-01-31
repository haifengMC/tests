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
			return NULL;
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
			COUT_LK(_id << " 线程启动...");

			std::mutex m;
			std::unique_lock<std::mutex> lk(m);

			while (!_close)
			{
				//TaskNode* pNode = NULL;
				COUT_LK(_id << " 线程进入循环，寻找可执行任务...");

				_runCv.wait(lk, [&]
					{
						if (!_pTask)
						{
							COUT_LK(_id << " 无任务，线程挂起...");
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
		COUT_LK(_id << " 工作线程创建...");
	}
}