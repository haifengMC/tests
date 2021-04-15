#include "global.h"
#include "hThread.h"
#include "hPoolMgr.h"

namespace hThread
{
	hTaskBase::hTaskBase(size_t weight, size_t thrdExpect, uint16_t attr = 0) :
		hTool::hUniqueMapVal<size_t, hTask>(_thisId, this),
		_stcData(weight, thrdExpect, attr) {}
	hTaskBase::hTaskBase(hTask::PhStcDt attr) :
		hTool::hUniqueMapVal<size_t, hTask>(_thisId, this),
		_stcData(attr) {}
	hTaskBase::hTaskBase(hTask&& t) :
		hTool::hUniqueMapVal<size_t, hTask>(_thisId, this),
		_stcData(std::move(t._stcData)), _dynData(std::move(t._dynData)) {}

	bool hTaskBase::init(PWhTaskMgr pMgr)
	{
		if (!pMgr)
			return false;

		if (!_stcData)
			return false;

		_dynData.emplace(pMgr, getThis<hTaskBase>());
		_dynData->setStat(TaskStatType::Init);

		return true;
	}

	size_t hTaskBase::getWeight() const
	{
		if (!_stcData)
			return 0;

		return _stcData->getWeight();
	}

	hNodeListIt hTaskBase::getNextNode()
	{
		if (!check())
		{
			checkErrOut();
			return hNodeListIt();
		}

		return _dynData->getNextNodeIt(
			_stcData->getBegNodeIt(),
			_stcData->getEndNodeIt(),
			_stcData->checkAttr(TaskAttrType::Loop));
	}

	bool hTaskBase::updateStat(TaskStatType state)
	{
		if (TaskStatType::Max <= state)
			return false;

		if (!check())
			return false;

		if (_dynData->checkStat(state))
			return false;

		return _dynData->updateStat(state);
	}

	bool hTaskBase::resetStatData()
	{
		if (!check())
		{
			checkErrOut();
			return false;
		}

		_dynData->resetData();
		return true;
	}
	
	bool hTaskBase::addThrdMem(PWhMemWork pMem)
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

		if (!pMem->checkStat(ThreadMemStatType::Wait))
		{
			COUT_LK(_thisId << "[" <<
				pMem->getStatName() <<
				pMem->getId() << "]线程不在等待状态...");
			return false;
		}

		if (!_dynData->checkStat(TaskStatType::Ready))
		{
			COUT_LK(_thisId << " 任务不在准备状态" <<
				_dynData->getStatName() << "...");
			return false;
		}

		auto nodeIt = getNextNode();
		if (!nodeIt._Ptr || nodeIt == _stcData->getEndNodeIt())
		{
			COUT_LK(_thisId << " 无可用节点...");
			return false;
		}

		auto memIt = _dynData->addThrdMem(pMem);
		pMem->initTask(getThis<hTask>(), nodeIt, memIt);

		return true;
	}

	//线程请求运行任务节点
	bool hTaskBase::runTaskNode(hNodeListIt nodeIt)
	{
		if (!check())
		{
			checkErrOut();
			return false;
		}

		if (!nodeIt._Ptr || nodeIt == _stcData->getEndNodeIt())
		{
			COUT_LK(_thisId << "无效节点");
			return false;
		}

		initCurNodeIt();
		updateStat(TaskStatType::Run);
		return true;
	}

	void hTaskBase::finishCurNode(hMemWorkListIt memIt)
	{
		if (!check())
		{
			checkErrOut();
			return;
		}

		_dynData->finishCurNode(memIt);
	}

	void hTaskBase::freeThrdMem(hMemWorkListIt memIt)
	{
		if (!check())
		{
			checkErrOut();
			return;
		}

		_dynData->freeThrdMem(memIt, _stcData->getEndNodeIt(), _stcData->getAttr());


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

	bool hTaskBase::check() const
	{
		if (!_stcData)
			return false;

		if (!_dynData)
			return false;

		return true;
	}

	void hTaskBase::checkErrOut() const
	{
		COUT_LK(_thisId << "任务异常,_stcData:" << _stcData <<
			"_dynData:" << _dynData << "...");
	}
}