#include "global.h"
#include "hThread.h"
#include "hPoolMgr.h"
#include "hTaskData.h"

namespace hThread
{
	namespace hTask
	{
		size_t hStaticDataMgr::getNeedThrdNum() const
		{
			size_t expectNum = _attrData.getExpectThrd();
			size_t nodeNum = _nodeData.getNodeNum();

			return std::min(expectNum, nodeNum);
		}

		hStaticDataMgr::hStaticDataMgr(size_t weight, size_t thrdExpect, const std::bitset<TaskAttrType::Max>& attr)
		{
			_weight = weight;
			_thrdExpect = thrdExpect;
			_attr = attr;
		}

		bool hDynamicDataMgr::finishCurNode(hWorkMemListIt memIt, hNodeListIt beg, hNodeListIt end, bool isLoop)
		{
			if (!_run.isValidThrdIt(memIt))
				return false;

			_run.incCurNodeIt(beg, end, isLoop);

			//������ȫ���������
			//if (TaskStatType::Finish == _state->_stateTy)
			//	return;

			(*memIt)->notifyNext(_run.getBegThrdIt(), _run.getEndThrdIt());
			return true;
		}

		void hDynamicDataMgr::freeThrdMem(hWorkMemListIt memIt, hNodeListIt end, size_t attr)
		{
			if (!_run.isValidThrdIt(memIt))
				return;

			if (!_run.eraseThrdMem(memIt))
				return;

			//�ڵ㻹δ�������ʱ�����쳣
			if (_run.isValidNodeIt(end))
			{
				COUT_LK(_pTask->getId() << "�ڵ㻹δ�������ʱ�����쳣...");
				_state.updateStat(TaskStatType::Error);
				return;
			}

			//���÷�����������ʱ�Ժ�ȴ�ɾ��
			if (attr & TaskAttrTypeBit::Detach)
			{
				COUT_LK(_pTask->getId() << "���÷�����������ʱ�Ժ�ȴ�ɾ��...");
				_state.updateStat(TaskStatType::Detach);
				return;
			} 

			//�����ظ����������ʱ�Żصȴ��ظ�ִ��
			if (attr & TaskAttrType::Repeat))
			{
				COUT_LK(_pTask->getId() << "�����ظ����������ʱ�Żصȴ��ظ�ִ��...");
				updateStat(TaskStatType::Wait);
				resetData();

				_pMgr->pushTask2Weight(_pTask);
				shPool.notifyMgrThrd();
				return;
			}

			updateStat(TaskStatType::Finish);
		}

		hDynamicDataMgr::hDynamicDataMgr(PWhTaskMgr pMgr, PWhTask pTask) :
			_state(pMgr, pTask), _run(pMgr, pTask)
		{
			_pMgr = pMgr;
			_pTask = pTask;
		}

		namespace hStatic
		{
			size_t hAttrData::getWeight() const
			{
				size_t weight = 0;
				readLk([&]() { weight = _weight; });
				return weight;
			}

			size_t hAttrData::getExpectThrd() const
			{
				size_t expectThrd = 0;
				readLk([&]() { expectThrd = _expectThrd; });
				return expectThrd;
			}

			size_t hAttrData::getAttr() const
			{
				size_t ret = 0;
				readLk([&]() { ret = _attr.to_ulong(); });
				return ret;
			}

			void hAttrData::setAttr(const std::bitset<TaskAttrType::Max>& attr)
			{
				writeLk([&]() { _attr = attr; });
			}

			bool hAttrData::checkAttr(TaskAttrType attr) const
			{
				if (TaskAttrType::Max <= attr)
					return false;

				bool ret = false;
				readLk([&]() { ret = _attr[attr]; });
				return ret;
			}

			bool hNodeData::addNode(hNode* pNode)
			{
				if (!pNode)
					return false;

				bool ret = true;
				writeLk([&]()
					{
						if (!_nodeData)
						{
							ret = false;
							return;
						}

						pNode->init(++_incId, _nodeData);
						_nodeList.push_back(hTool::hAutoPtr<hNode>(pNode));
					});

				return ret;
			}

			size_t hNodeData::getNodeNum() const
			{
				size_t nodeNum = 0;
				readLk([&]() { nodeNum = _nodeList.size(); });
				return nodeNum;
			}

			bool hNodeData::initNodeData(hUserData* pData)
			{
				writeLk([&]()
					{
						if (pData)
							_nodeData.bind(pData);
						else
							_nodeData.emplace();
					});

				return true;
			}

			hNodeListIt hNodeData::getBegNodeIt()
			{
				hNodeListIt it;
				readLk([&]() { it = _nodeList.begin(); });
				return it;
			}

			hNodeListIt hNodeData::getEndNodeIt()
			{
				hNodeListIt it;
				readLk([&]() { it = _nodeList.end(); });
				return it;
			}
		}

		namespace hDynamic
		{
			std::list<size_t>::iterator hStatData::getStatIt()
			{
				std::list<size_t>::iterator it;
				readLk([&]() { it = _stateIt; });
				return it;
			}

			TaskStatType hStatData::getStat() const
			{
				TaskStatType stat = TaskStatType::Max;
				readLk([&]() { stat = _stateTy; });
				return stat;
			}

			const char* hStatData::getStatName() const
			{
				const char* name = NULL;
				readLk([&]() { name = _stateTy.getName(); });
				return name;
			}

			void hStatData::setStat(TaskStatType stat) 
			{
				writeLk([&]() { _stateTy = stat; });
			}

			void hStatData::setStatIt(std::list<size_t>::iterator it)
			{
				writeLk([&]() { _stateIt = it; });
			}

			bool hStatData::updateStat(TaskStatType stat)
			{
				if (TaskStatType::Max <= stat)
					return false;

				bool ret = false;
				writeLk([&]()
					{
						if (_stateTy == stat)
							return;

						if (!_pMgr->updateTaskState(PWhTask->getId(), _stateIt, _stateTy, stat))
							return;

						_stateTy = stat;
						ret = true;
					});

				return ret;
			}

			bool hStatData::checkStat(TaskStatType stat) const
			{
				if (TaskStatType::Max <= stat)
					return false;

				bool ret = false;
				readLk([&]() { ret = _stateTy == stat; });
				return ret;
			}

			hStatData::hStatData(PWhTaskMgr pMgr, PWhTask pTask)
			{
				_pMgr = pMgr;
				_pTask = pTask;
			}

			hNodeListIt hRunData::getCurNodeIt()
			{
				hNodeListIt ret;
				readLk([&]() { ret = _curNodeIt; });
				return ret;
			}

			hNodeListIt hRunData::getNextNodeIt(hNodeListIt beg, hNodeListIt end, bool isLoop)
			{
				hNodeListIt it;
				writeLk([&]() 
					{ 
						if (!_nodeIt._Ptr)
						{
							it = _nodeIt = beg;
							return;
						}

						if (_nodeIt == end)
						{
							if (isLoop)
								it = _nodeIt = beg;
							else
								it = end;

							return;
						}

						if (++_nodeIt != end)
							it = _nodeIt;
					});

				if (_nodeIt._Ptr)
					return it;
				else
					return getNextNodeIt(beg, end, isLoop);
			}

			hWorkMemListIt hRunData::addThrdMem(PWhWorkMem pMem)
			{
				hWorkMemListIt it;
				writeLk([&]() { it = _thrds.insert(_thrds.end(), pMem); });
				return it;
			}

			void hRunData::initCurNodeIt(hNodeListIt initIt)
			{
				writeLk([&]() 
					{
						if (!_dynData->_curNodeIt._Ptr)
							_dynData->_curNodeIt = initIt;
					});

			}

			bool hRunData::isValidNodeIt(hNodeListIt end)
			{
				bool ret = true;
				readLk([&]()
					{
						if (_curNodeIt != end)
							return;

						if (_nodeIt != end)
							return;

						ret = false;
					});

				return ret;
			}

			bool hRunData::isValidThrdIt(hWorkMemListIt memIt)
			{
				if (!memIt._Ptr)
				{
					COUT_LK(_thisId << "����֪ͨ�սڵ�[1]...");
					return false;
				}

				bool ret = false;
				readLk([&]()
					{
						if (memIt == _thrds.end())
						{
							COUT_LK(_thisId << "����֪ͨ�սڵ�[2]...");
							return;
						}

						if (_thrds.empty())
						{
							COUT_LK(_thisId << "�����޿��ù����߳�...");
							return;
						}

						ret = true;
					});

				return ret;
			}

			void hRunData::incCurNodeIt(hNodeListIt beg, hNodeListIt end, bool isLoop)
			{
				writeLk([&]()
					{
						if (!_curNodeIt._Ptr)
						{
							_curNodeIt = beg;
							return;
						}

						if (_curNodeIt == end)
							return;

						++_curNodeIt;
						if (_curNodeIt == end && isLoop)
							_curNodeIt = beg;
					});
			}

			//����ڵ��������ͷ��߳�
			bool hRunData::eraseThrdMem(hWorkMemListIt memIt)
			{
				bool ret = false;
				writeLk([&]()
					{
						_thrds.erase(memIt);
						ret = _thrds.empty();
					});
				return ret;
			}

			bool hRunData::canProc(hNodeListIt it)
			{
				bool ret = false;
				readLk([&]() { ret = it == _curNodeIt; });
				return ret;
			}

			TaskStatType hRunData::checkFinishState(hNodeListIt end, size_t attr) const
			{
				TaskStatType ret = TaskStatType::Finish;
				readLk([&]() 
					{
						//�ڵ㻹δ�������ʱ�����쳣
						if (_curNodeIt != end || _nodeIt != end)
						{
							ret = TaskStatType::Error;
							COUT_LK(_pTask->getId() << "�ڵ㻹δ�������ʱ�����쳣...");
							return;
						}
						//���÷�����������ʱ�Ժ�ȴ�ɾ��
						if (attr & TaskAttrTypeBit::Detach)
						{
							ret = TaskStatType::Detach;
							COUT_LK(_pTask->getId() << "���÷�����������ʱ�Ժ�ȴ�ɾ��...");
							return;
						}
						//�����ظ����������ʱ�Żصȴ��ظ�ִ��
						if (attr & TaskAttrTypeBit::Repeat)
						{
							ret = TaskStatType::Wait;
							resetStatData();
							if (!canRepeat())
								return;

							_dynData->_pMgr->_weights.pushBack(getWeight(), getId());
							shPool.notifyMgrThrd();
							return;
						}

					});

				switch (ret)
				{
				case TaskStatType::Wait:
				default:
					break;
				}

				return ret;
			}

			hWorkMemListIt hRunData::getBegThrdIt()
			{
				hWorkMemListIt it;
				readLk([&]() { it = _thrds.begin(); });
				return it;
			}

			hWorkMemListIt hRunData::getEndThrdIt()
			{
				hWorkMemListIt it;
				readLk([&]() { it = _thrds.end(); });
				return it;
			}

			hRunData::hRunData(PWhTaskMgr pMgr, PWhTask pTask)
			{
				_pMgr = pMgr;
				_pTask = pTask;
			}
		}
	}
}