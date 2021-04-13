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
			COUT_LK(_thisId << " ���߳���ӵ�����...");
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
				pMem->getId() << "]�̲߳��ڵȴ�״̬...");
			return false;
		}

		if (!_dynData->checkStat(TaskStatType::Ready))
		{
			COUT_LK(_thisId << " ������׼��״̬" <<
				_dynData->getStatName() << "...");
			return false;
		}

		auto nodeIt = getNextNode();
		if (!nodeIt._Ptr || nodeIt == _stcData->getEndNodeIt())
		{
			COUT_LK(_thisId << " �޿��ýڵ�...");
			return false;
		}
		auto memIt = thrdsRef.insert(thrdsRef.end(), pMem);
		pMem->initTask(getThis<hTask>(), nodeIt, memIt);

		return true;
	}

	//�߳�������������ڵ�
	bool hTask::runTaskNode(hNodeListIt nodeIt)
	{
		if (!check())
		{
			checkErrOut();
			return false;
		}

		if (!nodeIt._Ptr || nodeIt == _stcData->_nodeList.end())
		{
			COUT_LK(_thisId << "��Ч�ڵ�");
			return false;
		}

		if (!_dynData->_curNodeIt._Ptr)
			_dynData->_curNodeIt = _stcData->_nodeList.begin();

#if 0
		//δ����ǰ�ӵ�һ���ڵ㿪ʼ�������
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
			COUT_LK(_thisId << "����֪ͨ�սڵ�...");
			return;
		}

		if (thrdList.empty())
		{
			COUT_LK(_thisId << "�����޿��ù����߳�...");
			return;
		}

		++_dynData->_curNodeIt;
		if (_dynData->_curNodeIt == _stcData->_nodeList.end() &&
			_stcData->_attr[TaskAttrType::Loop])
			_dynData->_curNodeIt = _stcData->_nodeList.begin();

		//������ȫ���������
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
			COUT_LK(_thisId << "�����ͷſ��߳�...");
			return;
		}

		thrdList.erase(memIt);
		if (thrdList.empty())
		{
			//�ڵ㻹δ�������ʱ�����쳣
			if (_dynData->_curNodeIt != _stcData->_nodeList.end() ||
				_dynData->_nodeIt != _stcData->_nodeList.end())
			{
				updateStat(TaskStatType::Error);
				return;
			}
			//���÷�����������ʱ�Ժ�ȴ�ɾ��
			if (checkAttr(TaskAttrType::Detach))
			{
				updateStat(TaskStatType::Detach);
				return;
			}
			//�����ظ����������ʱ�Żصȴ��ظ�ִ��
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
		COUT_LK(_thisId << "�����쳣,_stcData:" << _stcData <<
			"_dynData:" << _dynData << "...");
	}
}