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
			if (!pTData)//无效节点，直接删除
			{
				states[TaskStateType::Ready]->erase(itTData);
				continue;
			}
				
			Task* pTask = pTData->getTask();
			if (!pTask)//如果任务不存在，移入错误状态
			{
				spliceTasks(TaskStateType::Ready, TaskStateType::Error, &pTData, 1);
				continue;
			}

			//任务运行的线程
			size_t runThr = pTask->runTask(rate);
			if (!runThr)//无运行线程，移入等待状态
			{
				spliceTasks(TaskStateType::Ready, TaskStateType::Wait);
				break;
			}

			++ret;
			spliceTasks(TaskStateType::Ready, TaskStateType::Run, &pTData, 1);

			if (runThr >= numThr)//可用线程已耗尽
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

	bool TaskAttr::addNode(TaskNode* pNode)
	{
		if (!pNode)
			return false;

		if (!_nodeData)
			return false;

		pNode->init(++_incId, _nodeData);

		_nodeList.push_back(hTool::hAutoPtr<TaskNode>(pNode));
		return pNode;
	}

	bool TaskAttr::initNodeData(NodeData* pData)
	{
		if (pData)
			_nodeData.bind(pData);
		else
			_nodeData.emplace();

		return true;
	}

	std::ostream& TaskAttr::debugShow(std::ostream& os, uint8_t n, char c)
	{
		os << std::string(n++, c) << "[TaskAttr]" << 
			" weight:" << _weight << 
			" thrdExpect:" << _thrdExpect << 
			" incId" << _incId <<
			" attr:" << std::bitset<sizeof(_attr) * 8>(_attr).to_string();
		
		os << std::endl;
		if (_nodeData)
			_nodeData->debugShow(os, n, c);
		else
			os << std::string(n, c) << "[NodeData]NULL";

		os << std::endl;
		if (_nodeList.empty())
		{
			os << std::string(n, c) << "[TaskNode]NULL";
			return os;
		}

		bool first = true;
		for (auto& pNode : _nodeList)
		{
			if (first) first = false;
			else os << std::endl;

			if (pNode)
				pNode->debugShow(os, n, c);
			else
				os << std::string(n, c) << "[TaskNode]NULL";
		}

		return os;
	}

	TaskAttr::TaskAttr(size_t weight, size_t thrdExpect, uint16_t attr)
	{
		_weight = weight;
		_thrdExpect = thrdExpect;
		_attr = attr;
	}

	std::ostream& TaskStat::debugShow(std::ostream& os, uint8_t n, char c)
	{

		return os;
	}

	Task::Task(size_t weight, size_t thrdExpect, uint16_t attr) :
		hTool::hUniqueMapVal<size_t, Task>(_thisId, this),
		_attr(weight, thrdExpect, attr) {}

	Task::Task(hTool::hAutoPtr<TaskAttr> attr) :
		hTool::hUniqueMapVal<size_t, Task>(_thisId, this),
		_attr(attr) {}

	Task::Task(Task&& t) :
		hTool::hUniqueMapVal<size_t, Task>(_thisId, this),
		_attr(std::move(t._attr)), _stat(std::move(t._stat)) {}

	bool Task::init(/*TaskMgr* pMgr*/)
	{
		//if (!pMgr)
		//	return false;

		if (!_attr)
			return false;

		_stat.emplace();
		//stat->pMgr = pMgr;
		_stat->state = TaskStatType::Init; 
		_stat->nodeIt = _attr->_nodeList.end();

		return true;
	}

	bool Task::setStat(TaskStatType state)
	{
		if (TaskStatType::Max >= state)
			return false;

		if (!check())
			return false;

		if (_stat->state == state)
			return false;

		Task* pThis = this;
		//stat->pMgr->spliceTasks(stat->state, state, &pThis, 1);
		_stat->state = state;
		return true;
	}

	size_t Task::getWeight() const
	{
		if (!check())
			return 0;

		return _attr->_weight;
	}

	PTaskNode Task::getNextNode()
	{
		if (!check())
			return PTaskNode();

		NodeList& listRef = _attr->_nodeList;
		NodeListIt& itRef = _stat->nodeIt;

		if (itRef == listRef.end())
		{
			if (!(_attr->_attr & TaskAttrType::Loop))
				return PTaskNode();

			itRef = listRef.begin();

			if (itRef == listRef.end())
				return PTaskNode();
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

		//线程正在为任务工作
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

	//返回实际使用的线程数
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
	std::ostream& Task::debugShow(std::ostream& os, uint8_t n, char c)
	{
		os << std::string(n++, c) << "[Task]" << "thisId:" << _thisId;
		os << std::endl;
		if (_attr)
			_attr->debugShow(os, n);
		else
			os << std::string(n, c) << "[TaskAttr]NULL";
		os << std::endl;
		if (_stat)
			_stat->debugShow(os, n);
		else
			os << std::string(n, c) << "[TaskStat]NULL";

		return os;
	}

	bool Task::check() const
	{
		if (!_attr)
			return false;

		if (!_stat)
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