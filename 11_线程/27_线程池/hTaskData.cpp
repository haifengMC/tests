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

			hRunData::hRunData(PWhTaskMgr pMgr, PWhTask pTask)
			{
				_pMgr = pMgr;
				_pTask = pTask;
			}
		}
	}
}