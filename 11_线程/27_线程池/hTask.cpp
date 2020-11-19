#include "global.h"
#include "hThread.h"

namespace hThread
{
#define RD_LOCK sThreadPool.readLock()
#define RD_UNLOCK sThreadPool.readUnlock()
#define WT_LOCK sThreadPool.writeLock()
#define WT_UNLOCK sThreadPool.writeUnlock()

#if 0
	size_t TaskData::errId = 0;

	AllTasksData::AllTasksData() : tasksIdGen(tasks, 50) { tasksIdGen.resize(10000, 99999); }

	size_t AllTasksData::commitTasks(Task** task, size_t num)
	{
		size_t ret = 0;
		for (size_t n = 0; n < num; ++n)
		{
			auto rsPair = tasksIdGen.insert(task[n]);

			if (!rsPair.second)
			{
				DEL(task[n]);
				continue;
			}
				
			++ret;
			weights.pushBack(task[n]->getWeight(), &rsPair.first->second);
			
			std::list<TaskData*>& stRef = states[TaskStateType::Wait];
			auto rsState = stRef.insert(stRef.end(), &rsPair.first->second);
			rsPair.first->second.initItState(rsState);
		}
	}

	size_t AllTasksData::readyTasks(size_t num)
	{
		std::vector<TaskData*> tDataVec;
		size_t ret = RANDOM(hTool::RandomType::UniformDeInt, tDataVec, num, weights);
		spliceTasks(TaskStateType::Wait, TaskStateType::Ready, tDataVec);
	}

	void AllTasksData::cancelReadyTasks()
	{
		if (states[TaskStateType::Ready].empty())
			return;

		spliceTasks(TaskStateType::Ready, TaskStateType::Wait);
	}

	size_t AllTasksData::runTasks(size_t numThr, size_t rate)
	{
		if (!numThr || !rate)
			return 0;

		if (states[TaskStateType::Ready].empty())
			return 0;

		size_t ret = 0;

		for (auto itTData = states[TaskStateType::Ready].begin(); 
			itTData != states[TaskStateType::Ready]->end(); ++itTData)
		{
			TaskData* pTData = *itTData;
			if (!pTData)//��Ч�ڵ㣬ֱ��ɾ��
			{
				states[TaskStateType::Ready]->erase(itTData);
				continue;
			}
				
			Task* pTask = pTData->getTask();
			if (!pTask)//������񲻴��ڣ��������״̬
			{
				spliceTasks(TaskStateType::Ready, TaskStateType::Error, &pTData, 1);
				continue;
			}

			//�������е��߳�
			size_t runThr = pTask->runTask(rate);
			if (!runThr)//�������̣߳�����ȴ�״̬
			{
				spliceTasks(TaskStateType::Ready, TaskStateType::Wait);
				break;
			}

			++ret;
			spliceTasks(TaskStateType::Ready, TaskStateType::Run, &pTData, 1);

			if (runThr >= numThr)//�����߳��Ѻľ�
			{
				spliceTasks(TaskStateType::Ready, TaskStateType::Wait);
				break;
			}

			numThr -= runThr;
		}

		return ret;
	}

	size_t AllTasksData::pushTasks(Task** const& task, const size_t& num)
	{
		size_t ret = 0;
		for (size_t n = 0; n < num; ++n)
		{
			//if (idTasks.insert(std::make_pair(task[n]->getId(), task[n])).second)
			//	++ret, weights.pushBack(task[n]->getWeight(), task[n]);
			//else
			//	DEL(task[n]);
		}

		return ret;
	}

	size_t AllTasksData::popTasks(Task** const& task, const size_t& num)
	{
		size_t ret = RANDOM(hTool::RandomType::UniformDeInt, task, num, weights);

		for (size_t i = 0; i < ret; ++i)
			//idTasks.erase(task[i]->getId());

			return ret;
	}
#endif


	Task::Task(hTool::hAutoPtr<TaskAttr> attr) :
		hTool::hUniqueMapVal<size_t, Task>(thisId, this) 
	{
		this->attr = attr;
	}

	Task::Task(Task&& t) :
		hTool::hUniqueMapVal<size_t, Task>(thisId, this)
	{
		attr = std::move(t.attr);
		stat = std::move(t.stat);
	}

	bool Task::init(/*TaskMgr* pMgr*/)
	{
		//if (!pMgr)
		//	return false;

		if (!attr)
			return false;

		stat.emplace();
		//stat->pMgr = pMgr;
		stat->state = TaskStateType::Init; 
		stat->nodeIt = attr->nodeList.end();

		return true;
	}

	bool Task::setStat(TaskStateType state)
	{
		if (TaskStateType::Max >= state)
			return false;

		if (!check())
			return false;

		if (stat->state == state)
			return false;

		Task* pThis = this;
		//stat->pMgr->spliceTasks(stat->state, state, &pThis, 1);
		stat->state = state;
		return true;
	}

	size_t Task::getWeight() const
	{
		if (!check())
			return 0;

		return attr->weight;
	}

	TaskNode* Task::getNextNode()
	{
		if (!check())
			return NULL;

		NodeList& listRef = attr->nodeList;
		NodeListIt& itRef = stat->nodeIt;

		if (itRef == listRef.end())
		{
			if (!attr->loop)
				return NULL;

			itRef = listRef.begin();

			if (itRef == listRef.end())
				return NULL;
			else
				return *itRef;
		}

		if (++itRef == listRef.end())
			return getNextNode();
		else
			return *itRef;
	}

#if 0

	void Task::addThrd(ThreadMem* pMem)
	{
		if (!pMem)
			return;

		if (!check())
			return;

		ThrdList& thrdsRef = stat->thrds;

		//�߳�����Ϊ������
		if (pMem->pTask)
			return;
		pMem->pTask = this;

		auto itRBeg = thrdsRef.rbegin();
		pMem->itMem = thrdsRef.insert(thrdsRef.end(), pMem);
		ThrdListIt itBeg = thrdsRef.begin();

		if (itRBeg != thrdsRef.rend())
			(*itRBeg)->pNext = pMem;

		if (attr->loop)
			pMem->pNext = *itBeg;
		else
			pMem->pNext = NULL;

		pMem->pRwLock = sThreadPool.getRWLock(this);
		pMem->notify();
	}
#endif

#if 0

	//����ʵ��ʹ�õ��߳���
	size_t Task::runTask(const size_t& rate)
	{
		if (!check())
			return 0;

		RD_LOCK;
		size_t needRate = attr->thrdExpect < rate ? attr->thrdExpect : rate;
		size_t canNum = needRate < sThreadPool.readyThd.size() ? needRate : sThreadPool.readyThd.size();
		hRWLock* pRwLock = sThreadPool.getRWLock(this);
		RD_UNLOCK;

		pRwLock->writeLock();
		size_t n = 0;
		for (; n < canNum; ++n)
		{
			RD_LOCK;
			auto it = sThreadPool.readyThd.begin();
			RD_UNLOCK;
			if (it == sThreadPool.readyThd.end())
				break;
			RD_LOCK;
			ThreadMem* pMem = sThreadPool.memMgr[*it];
			RD_UNLOCK;
			if (!pMem)
				continue;

			addThrd(pMem);
		}
		pRwLock->writeUnlock();

		return n;
	}
#endif

	bool Task::check() const
	{
		if (!attr)
			return false;

		if (!stat)
			return false;

		//if (!stat->pMgr)
		//	return false;

		return true;
	}

#undef RD_LOCK
#undef RD_UNLOCK
#undef WT_LOCK
#undef WT_UNLOCK
}