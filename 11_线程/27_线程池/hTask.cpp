#include "global.h"
#include "hThread.h"
#include "hPoolMgr.h"

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

	hTask::hTask(size_t weight, size_t thrdExpect, uint16_t attr) :
		hTool::hUniqueMapVal<size_t, hTask>(_thisId, this),
		_stcData(weight, thrdExpect, attr) {}

	hTask::hTask(hTool::hAutoPtr<hTaskStaticData> attr) :
		hTool::hUniqueMapVal<size_t, hTask>(_thisId, this),
		_stcData(attr) {}

	hTask::hTask(hTask&& t) :
		hTool::hUniqueMapVal<size_t, hTask>(_thisId, this),
		_stcData(std::move(t._stcData)), _dynData(std::move(t._dynData)) {}

	bool hTask::init(PWhTaskMgr pMgr)
	{
		if (!pMgr)
			return false;

		if (!_stcData)
			return false;

		_dynData.emplace();
		_dynData->_pMgr = pMgr;
		_dynData->_stateTy = TaskStatType::Init; 

		return true;
	}

	size_t hTask::getWeight() const
	{
		if (!check())
			return 0;

		return _stcData->_weight;
	}

	hNodeListIt hTask::getNextNode()
	{
		if (!check())
		{
			checkErrOut();
			return hNodeListIt();
		}

		hNodeList& nodeList = _stcData->_nodeList;
		hNodeListIt& nodeIt = _dynData->_nodeIt;

		if (!nodeIt._Ptr)
		{
			nodeIt = nodeList.begin();
			return nodeIt;
		}

		if (nodeIt == nodeList.end())
		{
			if (!_stcData->_attr[TaskAttrType::Loop])
				return nodeList.end();

			nodeIt = nodeList.begin();
			return nodeIt;
		}

		if (++nodeIt == nodeList.end())
			return getNextNode();
		else
			return nodeIt;
	}

	bool hTask::checkAttr(TaskAttrType attr)
	{
		if (!_stcData)
			return false;

		if (TaskAttrType::Max <= attr)
			return false;

		return _stcData->_attr[attr];
	}

	bool hTask::checkStat(TaskStatType stat)
	{
		if (!_dynData)
			return false;

		_dynData->checkStat(stat);
	}

	bool hTask::setStat(TaskStatType state)
	{
		if (TaskStatType::Max <= state)
			return false;

		if (!check())
			return false;

		if (_dynData->_stateTy == state)
			return false;

		_dynData->_stateTy = state;
		return true;
	}

	bool hTask::updateStat(TaskStatType state)
	{
		if (TaskStatType::Max <= state)
			return false;

		if (!check())
			return false;

		if (_dynData->_stateTy == state)
			return false;

		std::list<size_t>* newList = _dynData->_pMgr->getStateList(state);
		if (!newList)
			return false;

		std::list<size_t>* oldList = _dynData->_pMgr->getStateList(_dynData->_stateTy);
		std::list<size_t>::iterator& it = _dynData->_stateIt;
		if (!it._Ptr || !oldList || it == oldList->end())
			it = newList->insert(newList->end(), _thisId);
		else
			newList->splice(newList->end(), *oldList, it);
		_dynData->_stateTy = state;

		return true;
	}

	bool hTask::resetStatData()
	{
		if (!check())
		{
			checkErrOut();
			return false;
		}

		_dynData->resetData();
		return true;
	}
	
	bool hTask::addThrdMem(PWhMemWork pMem)
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

		if (TaskStatType::Ready != _dynData->_stateTy)
		{
			COUT_LK(_thisId << " 任务不在准备状态" <<
				_dynData->_stateTy.getName() << "...");
			return false;
		}

		hMemWorkList& thrdsRef = _dynData->_thrds;
		auto nodeIt = getNextNode();
		if (!nodeIt._Ptr || nodeIt == _stcData->_nodeList.end())
		{
			COUT_LK(_thisId << " 无可用节点...");
			return false;
		}
		auto memIt = thrdsRef.insert(thrdsRef.end(), pMem);
		pMem->initTask(getThis<hTask>(), nodeIt, memIt);
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
	bool hTask::runTaskNode(hNodeListIt nodeIt)
	{
		if (!check())
		{
			checkErrOut();
			return false;
		}

		if (!nodeIt._Ptr || nodeIt == _stcData->_nodeList.end())
		{
			COUT_LK(_thisId << "无效节点");
			return false;
		}

		if (!_dynData->_curNodeIt._Ptr)
			_dynData->_curNodeIt = _stcData->_nodeList.begin();

#if 0
		//未加锁前从第一个节点开始逐个运行
		if (_state->_curNodeIt != nodeIt)
			return false;
#endif
		updateStat(TaskStatType::Run);
		return true;
	}

	void hTask::finishCurNode(hMemWorkListIt memIt)
	{
		if (!check())
		{
			checkErrOut();
			return;
		}

		hMemWorkList& thrdList = _dynData->_thrds;
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

		++_dynData->_curNodeIt;
		if (_dynData->_curNodeIt == _stcData->_nodeList.end() &&
			_stcData->_attr[TaskAttrType::Loop])
			_dynData->_curNodeIt = _stcData->_nodeList.begin();

		//任务已全部分配完成
		//if (TaskStatType::Finish == _state->_stateTy)
		//	return;

		hMemWorkListIt nextIt = std::next(memIt);
		if (nextIt == thrdList.end())
			nextIt = thrdList.begin();

		if (nextIt != memIt && nextIt != thrdList.end())
			(*nextIt)->notify();
	}

	void hTask::freeThrdMem(hMemWorkListIt memIt)
	{
		if (!check())
		{
			checkErrOut();
			return;
		}

		hMemWorkList& thrdList = _dynData->_thrds;
		if (!memIt._Ptr || memIt == thrdList.end())
		{
			COUT_LK(_thisId << "任务释放空线程...");
			return;
		}

		thrdList.erase(memIt);
		if (thrdList.empty())
		{
			//节点还未运行完毕时任务异常
			if (_dynData->_curNodeIt != _stcData->_nodeList.end() ||
				_dynData->_nodeIt != _stcData->_nodeList.end())
			{
				updateStat(TaskStatType::Error);
				return;
			}
			//设置分离的任务完成时稍后等待删除
			if (checkAttr(TaskAttrType::Detach))
			{
				updateStat(TaskStatType::Detach);
				return;
			}
			//设置重复的任务完成时放回等待重复执行
			if (checkAttr(TaskAttrType::Repeat))
			{
				updateStat(TaskStatType::Wait);
				resetStatData();
				if (!canRepeat())
					return;
				
				_dynData->_pMgr->_weights.pushBack(getWeight(), getId());
				shPool.notifyMgrThrd();
				return;
			}
			
			updateStat(TaskStatType::Finish);
		}
	}

	size_t hTask::calcNeedThrdNum(size_t curThrd)
	{
		if (!_stcData)
			return 0;

		return std::min({curThrd, _stcData->_thrdExpect, _stcData ->_nodeList.size()});
	}

	bool hTask::check() const
	{
		if (!_stcData)
			return false;

		if (!_dynData)
			return false;

		if (!_dynData->_pMgr)
			return false;

		return true;
	}

	void hTask::checkErrOut() const
	{
		COUT_LK(_thisId << "任务异常,_attrb:" << _stcData <<
			"_state:" << _dynData <<
			"_pMgr" << (_dynData ? (bool)_dynData->_pMgr : false) << "...");

	}

#undef RD_LOCK
#undef RD_UNLOCK
#undef WT_LOCK
#undef WT_UNLOCK
}