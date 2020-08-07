#include "global.h"
#include "hThread.h"

namespace hThread
{
#define RD_LOCK sThreadPool.readLock()
#define RD_UNLOCK sThreadPool.readUnlock()
#define WT_LOCK sThreadPool.writeLock()
#define WT_UNLOCK sThreadPool.writeUnlock()

	TaskNode* Task::getNextNode()
	{
		if (nodeIt == nodeList.end())
		{
			if (!loop)
				return NULL;

			nodeIt = nodeList.begin();

			if (nodeIt == nodeList.end())
				return NULL;
			else
				return *nodeIt;
		}

		if (++nodeIt == nodeList.end())
			return getNextNode();
		else
			return *nodeIt;
	}

	//返回实际使用的线程数
	size_t Task::runTask(const size_t& rate)
	{
		size_t needRate = thrdExpect < rate ? thrdExpect : rate;
		RD_LOCK;
		size_t canNum = needRate < sThreadPool.readyThd.size() ? needRate : sThreadPool.readyThd.size();
		RD_UNLOCK;
		size_t n = 0;
		for (;n < canNum; ++n)
		{
			RD_LOCK;
			auto it = sThreadPool.readyThd.begin();
			if (it == sThreadPool.readyThd.end())
				break;
			ThreadMem* pMem = sThreadPool.memMgr[*it];
			if (!pMem)
				break;
			RD_UNLOCK;
			pMem->runTask(this);
		}

		return n;
	}

#undef RD_LOCK
#undef RD_UNLOCK
#undef WT_LOCK
#undef WT_UNLOCK
}