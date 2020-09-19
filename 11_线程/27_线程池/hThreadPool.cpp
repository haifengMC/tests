#include "global.h"
#include "hThread.h"
#include "hThreadPoolMgr.h"

namespace hThread
{
#define RD_LOCK sThreadPool.readLock()
#define RD_UNLOCK sThreadPool.readUnlock()
#define WT_LOCK sThreadPool.writeLock()
#define WT_UNLOCK sThreadPool.writeUnlock()

	std::mutex coutM;
#define	_PUTOUT_D
#define COUT_LK(x)
#ifdef _PUTOUT_D 
#define COUT_LK(x) \
	{ \
		std::lock_guard<std::mutex> lk(coutM); \
		std::cout << x << std::endl; \
	}
#endif // _PUTOUT_D 

	ThreadMem::ThreadMem(const size_t& id) : id(id),
		func([&]()
		{
			COUT_LK(this->id << " 线程启动...");

			std::mutex m;
			std::unique_lock<std::mutex> lk(m);

			while (!isClose())
			{
				TaskNode* pNode = NULL;

				COUT_LK(this->id << " 线程等待执行任务...");
				runCv.wait(lk, [&]
					{
						if (!pTask || !pNext || !pRwLock)
							return false;

						pRwLock->readLock();
						bool isFailed = pTask->failed;
						pRwLock->readUnlock();

						pRwLock->writeLock();
						pNode = pTask->getNextNode();
						pRwLock->writeUnlock();

						if (!pNode)//获取节点失败
							isFailed = true;

						if (isFailed)//任务失效释放内存
						{
							pRwLock->writeLock();
							DEL(pTask);
							pNext = NULL;
							pRwLock->writeUnlock();
							return false;
						}

						return true;
					});

				while (pNode)
				{
					if (!pNode->initProc())
					{
						pRwLock->writeLock();
						pTask->running = false;
						pTask->failed = true;
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

			}
			sThreadPool.removeThrd(id);
		}),
		thrd(func)
	{
		COUT_LK(id << " 线程创建...");
		thrd.detach();
	}

	ThreadMem::~ThreadMem()
	{
		COUT_LK(id << " 线程释放...");
	}
#undef COUT_LK

	void ThreadMem::runTask(Task* const& task)
	{
		WT_LOCK;
		pTask = task;
		task->addThrd(this);
		WT_UNLOCK;
		runCv.notify_one();//应当为本线程打开自锁，在任务锁前打开，任务锁应在添加完任务后由任务打开
	}

	ThreadPool::ThreadPool() : 
		_invalid(sTreadPoolMgr), 
		base(sTreadPoolMgr.getBaseCfg()){ init(); }

	ThreadPool::~ThreadPool() { final(); }

	void ThreadPool::init()
	{
		if (_invalid)
		{//Err
			return;
		}
		for (auto& item : sTreadPoolMgr.getTaskMgrCfg())
			taskMgr.emplace_back(item.second);

		createThrd(base.initThd);
	}

	void ThreadPool::final()
	{
		for (auto& pMem : memMgr)
			DEL(pMem);
	}

	void ThreadPool::run()
	{
	}

	void ThreadPool::stop()
	{
	}

	bool ThreadPool::commitTasks(Task** const& task, const size_t& num, TaskMgrPriority priority)
	{
		if (!task || TaskMgrPriority::Max <= priority)
			return false;

		taskMgr[(size_t)priority].pushTasks(task, num);
	}

	hRWLock* ThreadPool::getRWLock(Task* pTask)
	{
		if (!pTask)
			return NULL;

		auto it = taskLock.find(pTask);
		if (it != taskLock.end())
			return it->second;

		return taskLock[pTask] = new hRWLock;
	}

	void ThreadPool::createThrd(const size_t& num)
	{
		rwLock.writeLock();
		for (size_t i = 0; i < num; ++i)
		{
			memMgr.push_back(new ThreadMem(memMgr.size()));
			readyThd.insert(memMgr.back()->getId());
		}

		rwLock.writeUnlock();
	}
	void ThreadPool::closeThrd(const size_t& id)
	{
		rwLock.writeLock();
		memMgr[id]->close();
		rwLock.writeUnlock();
	}

	void ThreadPool::runThrd(const size_t& num)
	{
		rwLock.readLock();
		size_t needNum = readyThd.size() < num ? readyThd.size() : num;
		rwLock.readUnlock();
		//预期运行任务数为0或没有可用线程不处理
		if (!needNum)
			return;

		//Task** pTasks = new Task*[needNum];
		//size_t begNum = 0;

		for (auto& mgr : taskMgr)
		{
			rwLock.writeLock();
			size_t canNum = mgr.readyTasks(needNum, busyThd.size());
			rwLock.writeUnlock();

			if (!canNum)
				continue;

			rwLock.readLock();
			//任务可以获取线程的倍率
			size_t canRate = 1.5 * readyThd.size() / canNum;
			rwLock.readUnlock();
			//已运行的任务数
			size_t runNum = mgr.runTasks(canNum, canRate);

			if (needNum <= runNum)//需求任务都运行则不再运行新的
				break;

			needNum -= runNum;
		}
	}

	void ThreadPool::removeThrd(const size_t& id)
	{
		rwLock.writeLock();

		DEL(memMgr[id]);
		memMgr[id] = *memMgr.rbegin();
		memMgr[id]->setId(id);
		memMgr.pop_back();
		readyThd.erase(id);

		rwLock.writeUnlock();
	}

#undef RD_LOCK
#undef RD_UNLOCK
#undef WT_LOCK
#undef WT_UNLOCK
}