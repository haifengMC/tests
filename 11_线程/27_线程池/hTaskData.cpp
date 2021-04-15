#include "global.h"
#include "hThread.h"
#include "hPoolMgr.h"

namespace hThread
{
	namespace hTask
	{
		hStaticDataMgr::hStaticDataMgr(size_t weight, size_t thrdExpect, const std::bitset<TaskAttrType::Max>& attr)
		{
			_weight = weight;
			_thrdExpect = thrdExpect;
			_attr = attr;
		}

		bool hDynamicDataMgr::finishCurNode(hMemWorkListIt memIt, hNodeListIt beg, hNodeListIt end, bool isLoop)
		{
			if (!_run.isValidThrdIt(memIt))
				return false;

			_run.incCurNodeIt(beg, end, isLoop);

			//任务已全部分配完成
			//if (TaskStatType::Finish == _state->_stateTy)
			//	return;

			memIt->notifyNext(_run.getBegThrdIt(), _run.getEndThrdIt());
			return true;
		}

		void hDynamicDataMgr::freeThrdMem(hMemWorkListIt memIt, hNodeListIt end, size_t attr)
		{
			if (!_run.isValidThrdIt(memIt))
				return;

			if (!_run.eraseThrdMem(memIt))
				return;


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

			hMemWorkListIt hRunData::addThrdMem(PWhMemWork pMem)
			{
				hMemWorkListIt it;
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

			bool hRunData::isValidThrdIt(hMemWorkListIt memIt)
			{
				if (!memIt._Ptr)
				{
					COUT_LK(_thisId << "任务通知空节点[1]...");
					return false;
				}

				bool ret = false;
				readLk([&]()
					{
						if (memIt == _thrds.end())
						{
							COUT_LK(_thisId << "任务通知空节点[2]...");
							return;
						}

						if (_thrds.empty())
						{
							COUT_LK(_thisId << "任务无可用工作线程...");
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

			//任务节点分配完成释放线程
			bool hRunData::eraseThrdMem(hMemWorkListIt memIt)
			{
				bool ret = false;
				writeLk([&]()
					{
						_thrds.erase(memIt);
						ret = _thrds.empty();
					});
				return ret;
			}

			TaskStatType hRunData::checkFinishState(hNodeListIt end, size_t attr) const
			{
				TaskStatType ret = TaskStatType::Finish;
				readLk([&]() 
					{
						//节点还未运行完毕时任务异常
						if (_curNodeIt != end || _nodeIt != end)
						{
							ret = TaskStatType::Error;
							COUT_LK(_pTask->getId() << "节点还未运行完毕时任务异常...");
							return;
						}
						//设置分离的任务完成时稍后等待删除
						if (attr & TaskAttrTypeBit::Detach)
						{
							ret = TaskStatType::Detach;
							COUT_LK(_pTask->getId() << "设置分离的任务完成时稍后等待删除...");
							return;
						}
						//设置重复的任务完成时放回等待重复执行
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

			hMemWorkListIt hRunData::getBegThrdIt()
			{
				hMemWorkListIt it;
				readLk([&]() { it = _thrds.begin(); });
				return it;
			}

			hMemWorkListIt hRunData::getEndThrdIt()
			{
				hMemWorkListIt it;
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