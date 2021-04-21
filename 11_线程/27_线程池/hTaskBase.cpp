#include "global.h"
#include "hThread.h"
#include "hPoolMgr.h"

namespace hThread
{
	hTaskBase::hTaskBase(size_t weight, size_t thrdExpect, uint16_t attr) :
		hTool::hUniqueMapVal<size_t, hTaskBase>(_thisId, this),
		_stcData(weight, thrdExpect, attr) {}
	hTaskBase::hTaskBase(hTask::PhStcDt attr) :
		hTool::hUniqueMapVal<size_t, hTaskBase>(_thisId, this),
		_stcData(attr) {}
	hTaskBase::hTaskBase(hTaskBase&& t) :
		hTool::hUniqueMapVal<size_t, hTaskBase>(_thisId, this),
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

	size_t hTaskBase::getNeedThrdNum() const
	{
		if (!_stcData)
			return 0;

		return _stcData->getNeedThrdNum();
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

	hNodeListIt hTaskBase::getCurNodeIt()
	{
		if (!_dynData)
			return hNodeListIt();

		return _dynData->getCurNodeIt();
	}

	TaskStatType hTaskBase::getStat() const
	{
		if (!_dynData)
			return TaskStatType::Max;

		return _dynData->getStat();
	}

	std::list<size_t>::iterator hTaskBase::getStatIt()
	{
		if (!_dynData)
			return std::list<size_t>::iterator();

		return _dynData->getStatIt();
	}

	bool hTaskBase::checkStat(TaskStatType state) const
	{
		if (!_dynData)
			return false;

		return _dynData->checkStat(state);
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

	void hTaskBase::setStat(TaskStatType state)
	{ 
		if (!_dynData)
			return;
		
		_dynData->setStat(state); 
	}

	void hTaskBase::setStatIt(std::list<size_t>::iterator it)
	{
		if (!_dynData)
			return;

		_dynData->setStatIt(it);
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
	
	bool hTaskBase::addThrdMem(PWhWorkMem pMem)
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
		pMem->initTask(getThis<hTaskBase>(), nodeIt, memIt);

		return true;
	}

	void hTaskBase::initCurNodeIt()
	{
		if (!_dynData)
			return;

		_dynData->initCurNodeIt(_stcData->getBegNodeIt());
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

	void hTaskBase::finishCurNode(hWorkMemListIt memIt)
	{
		if (!check())
		{
			checkErrOut();
			return;
		}

		_dynData->finishCurNode(memIt, _stcData->getBegNodeIt(), _stcData->getEndNodeIt(), _stcData->checkAttr(TaskAttrType::Loop));
	}

	void hTaskBase::freeThrdMem(hWorkMemListIt memIt)
	{
		if (!check())
		{
			checkErrOut();
			return;
		}

		_dynData->freeThrdMem(memIt, _stcData->getEndNodeIt(), _stcData->getAttr());
	}

	size_t hTaskBase::calcNeedThrdNum(size_t curThrd)
	{
		if (!check())
		{
			checkErrOut();
			return 0;
		}

		if (!curThrd)
			return 0;

		return std::min({curThrd, _stcData->getNeedThrdNum()});
	}

	bool hTaskBase::canProc(hNodeListIt it)
	{
		if (!_dynData)
			return false;

		return _dynData->canProc(it);
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