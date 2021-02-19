#include "global.h"
#include "hThread.h"
#include "hThreadPoolMgr.h"

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

	TaskAttr::TaskAttr(size_t weight, size_t thrdExpect, const std::bitset<TaskAttrType::Max>& attr)
	{
		_weight = weight;
		_thrdExpect = thrdExpect;
		_attr = attr;
	}

	Task::Task(size_t weight, size_t thrdExpect, uint16_t attr) :
		hTool::hUniqueMapVal<size_t, Task>(_thisId, this),
		_attrb(weight, thrdExpect, attr) {}

	Task::Task(hTool::hAutoPtr<TaskAttr> attr) :
		hTool::hUniqueMapVal<size_t, Task>(_thisId, this),
		_attrb(attr) {}

	Task::Task(Task&& t) :
		hTool::hUniqueMapVal<size_t, Task>(_thisId, this),
		_attrb(std::move(t._attrb)), _state(std::move(t._state)) {}

	bool Task::init(PWTaskMgr pMgr)
	{
		if (!pMgr)
			return false;

		if (!_attrb)
			return false;

		_state.emplace();
		_state->_pMgr = pMgr;
		_state->_stateTy = TaskStatType::Init; 

		return true;
	}

	size_t Task::getWeight() const
	{
		if (!check())
			return 0;

		return _attrb->_weight;
	}

	NodeListIt Task::getNextNode()
	{
		if (!check())
		{
			checkErrOut();
			return NodeListIt();
		}

		NodeList& nodeList = _attrb->_nodeList;
		NodeListIt& nodeIt = _state->_nodeIt;

		if (!nodeIt._Ptr)
		{
			nodeIt = nodeList.begin();
			return nodeIt;
		}

		if (nodeIt == nodeList.end())
		{
			if (!_attrb->_attr[TaskAttrType::Loop])
				return nodeList.end();

			nodeIt = nodeList.begin();
			return nodeIt;
		}

		if (++nodeIt == nodeList.end())
			return getNextNode();
		else
			return nodeIt;
	}

	bool Task::checkAttr(TaskAttrType attr)
	{
		if (!_attrb)
			return false;

		if (TaskAttrType::Max <= attr)
			return false;

		return _attrb->_attr[attr];
	}

	bool Task::setStat(TaskStatType state)
	{
		if (TaskStatType::Max <= state)
			return false;

		if (!check())
			return false;

		if (_state->_stateTy == state)
			return false;

		_state->_stateTy = state;
		return true;
	}

	bool Task::updateStat(TaskStatType state)
	{
		if (TaskStatType::Max <= state)
			return false;

		if (!check())
			return false;

		if (_state->_stateTy == state)
			return false;

		std::list<size_t>* newList = _state->_pMgr->getStateList(state);
		if (!newList)
			return false;

		std::list<size_t>* oldList = _state->_pMgr->getStateList(_state->_stateTy);
		std::list<size_t>::iterator& it = _state->_stateIt;
		if (!it._Ptr || !oldList || it == oldList->end())
			it = newList->insert(newList->end(), _thisId);
		else
			newList->splice(newList->end(), *oldList, it);
		_state->_stateTy = state;

		return true;
	}
	
	bool Task::addThrdMem(PWThrdMemWork pMem)
	{
		if (!pMem)
		{
			COUT_LK(_thisId << " 空线程添加到任务...");
			return false;
		}

		if (!check())
		{
			checkErrOut();
			return false;
		}

		if (ThreadMemStatType::Wait != pMem->getStat())
		{
			COUT_LK(_thisId << "[" <<
				pMem->getStat().getName() <<
				pMem->getId() << "]线程不在等待状态...");
			return false;
		}

		if (TaskStatType::Ready != _state->_stateTy)
		{
			COUT_LK(_thisId << " 任务不在准备状态" <<
				_state->_stateTy.getName() << "...");
			return false;
		}

		ThrdMemWorkList& thrdsRef = _state->_thrds;
		auto nodeIt = getNextNode();
		if (!nodeIt._Ptr || nodeIt == _attrb->_nodeList.end())
		{
			COUT_LK(_thisId << " 无可用节点...");
			return false;
		}
		auto memIt = thrdsRef.insert(thrdsRef.end(), pMem);
		pMem->initTask(*getThis<Task>(), nodeIt, memIt);
#if 0
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
#endif
		return true;
	}

	//线程请求运行任务节点
	bool Task::runTaskNode(NodeListIt nodeIt)
	{
		if (!check())
		{
			checkErrOut();
			return false;
		}

		if (!nodeIt._Ptr || nodeIt == _attrb->_nodeList.end())
		{
			COUT_LK(_thisId << "无效节点");
			return false;
		}

		if (!_state->_curNodeIt._Ptr)
			_state->_curNodeIt = _attrb->_nodeList.begin();

#if 0
		//未加锁前从第一个节点开始逐个运行
		if (_state->_curNodeIt != nodeIt)
			return false;
#endif
		updateStat(TaskStatType::Run);
		return true;
	}

	void Task::finishCurNode(ThrdMemWorkListIt memIt)
	{
		if (!check())
		{
			checkErrOut();
			return;
		}

		ThrdMemWorkList& thrdList = _state->_thrds;
		if (!memIt._Ptr || memIt == thrdList.end())
		{
			COUT_LK(_thisId << "任务通知空节点...");
			return;
		}

		if (thrdList.empty())
		{
			COUT_LK(_thisId << "任务无可用工作线程...");
			return;
		}

		++_state->_curNodeIt;
		if (_state->_curNodeIt == _attrb->_nodeList.end() &&
			_attrb->_attr[TaskAttrType::Loop])
			_state->_curNodeIt = _attrb->_nodeList.begin();

		//任务已全部分配完成
		//if (TaskStatType::Finish == _state->_stateTy)
		//	return;

		ThrdMemWorkListIt nextIt = std::next(memIt);
		if (nextIt == thrdList.end())
			nextIt = thrdList.begin();

		if (nextIt != memIt && nextIt != thrdList.end())
			(*nextIt)->notify();
	}

	void Task::freeThrdMem(ThrdMemWorkListIt memIt)
	{
		if (!check())
		{
			checkErrOut();
			return;
		}

		ThrdMemWorkList& thrdList = _state->_thrds;
		if (!memIt._Ptr || memIt == thrdList.end())
		{
			COUT_LK(_thisId << "任务释放空线程...");
			return;
		}

		thrdList.erase(memIt);
		if (thrdList.empty())
		{
			//节点还未运行完毕时任务异常
			if (_state->_curNodeIt != _attrb->_nodeList.end() ||
				_state->_nodeIt != _attrb->_nodeList.end())
				updateStat(TaskStatType::Error);
			//设置分离的任务完成时稍后等待删除
			else if (checkAttr(TaskAttrType::Detach))
				updateStat(TaskStatType::Detach);
			else
				updateStat(TaskStatType::Finish);
		}
	}

	size_t Task::calcNeedThrdNum(size_t curThrd)
	{
		if (!_attrb)
			return 0;

		return std::min({curThrd, _attrb->_thrdExpect, _attrb ->_nodeList.size()});
	}

	bool Task::check() const
	{
		if (!_attrb)
			return false;

		if (!_state)
			return false;

		if (!_state->_pMgr)
			return false;

		return true;
	}

	void Task::checkErrOut() const
	{
		COUT_LK(_thisId << "任务异常,_attrb:" << _attrb <<
			"_state:" << _state <<
			"_pMgr" << (_state ? (bool)_state->_pMgr : false) << "...");

	}

#undef RD_LOCK
#undef RD_UNLOCK
#undef WT_LOCK
#undef WT_UNLOCK
}