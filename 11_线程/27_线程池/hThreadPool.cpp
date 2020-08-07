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
#define COUT_LK(x) { std::lock_guard<std::mutex> lk(coutM); std::cout << x << std::endl; }

	void ThreadMemFunc::operator() ()
	{
		std::mutex m;
		std::unique_lock<std::mutex> lk(m);

		while (!isClose())
		{
			runCv.wait(lk, [&]
				{
					if (!pTask)
						return false;

					return true;
				});
			TaskNode* pNode = NULL;
			while (pNode = pTask->getNextNode())
			{
				if (pNode->preProcess())
					pNode->onProcess();
				pNode->afterProcess();
			}

		}
		sThreadPool.removeThrd(id);
	}
#undef COUT_LK

	ThreadMem::ThreadMem(const size_t& id) : id(id), 
		func(this->id, this->pTask, runCv), thrd(func)
	{ 
		thrd.detach(); 
	}


	void ThreadMem::runTask(Task* const& task)
	{
		WT_LOCK;
		pTask = task;
		task->insertThrd(id);
		WT_UNLOCK;
		func.runCv.notify_one();
	}

	const bool& ThreadMemFunc::isClose() const
	{
		return sThreadPool.memMgr[id]->isClose();
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

	void ThreadPool::createThrd(const size_t& num)
	{
		rwLock.writeLock();
		for (size_t i = 0; i < num; ++i)
			memMgr.push_back(new ThreadMem(memMgr.size()));

		readyThd.insert(memMgr.back()->getId());
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
		if (!num)
			return;

		rwLock.readLock();
		size_t needNum = readyThd.size() < num ? readyThd.size() : num;
		rwLock.readUnlock();
		Task** pTasks = new Task*[needNum];

		for (auto& mgr : taskMgr)
		{
			rwLock.writeLock();
			size_t canNum = mgr.popTasks(pTasks, needNum);
			rwLock.writeUnlock();
			
			if (!canNum)
				continue;

			rwLock.readLock();
			size_t canRate = readyThd.size() * 3 / canNum / 2;
			rwLock.readUnlock();
			size_t useNum = runTasks(pTasks, canNum, canRate);
			if (needNum <= useNum)
				break;
			needNum -= useNum;
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

	size_t ThreadPool::runTasks(Task**& pTasks, const size_t& num, const size_t& rate)
	{
		if (!pTasks || !num || !rate)
			return 0;

		size_t ret = 0;

		for (size_t n = 0; n < num; ++n)
			ret += pTasks[n]->runTask(rate);

		return ret;
	}

#undef RD_LOCK
#undef RD_UNLOCK
#undef WT_LOCK
#undef WT_UNLOCK
}