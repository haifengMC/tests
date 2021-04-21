#include "global.h"
#include "hTool.h"
#include "hThread.h"
#include "hPoolMgr.h"

namespace hThread
{
	namespace hTaskMgr
	{
		TaskMgrPriority hCfgData::getId() const
		{
			TaskMgrPriority ret;
			readLk([&]() { ret = _base.index(); });
			return ret;
		}

		const char* hCfgData::getName() const
		{
			const char* ret = 0;
			readLk([&]() { ret = _base.index().getName(); });
			return ret;
		}

		size_t hCfgData::getMaxBusyThd() const
		{
			size_t ret = 0;
			readLk([&]() { ret = _base.data.maxBusyThd; });
			return ret;
		}

		hCfgData::hCfgData(PWhTaskMgr pMgr, const TaskMgrCfgItem& base) :
			_pMgr(pMgr), _base(base) {}

		auto hTaskMgrData::insertTask(PhTask pTask) ->
			std::pair<std::map<size_t, hTool::hAutoPtr<hTaskBase>>::iterator, bool>
		{
			std::pair <std::map<size_t, hTool::hAutoPtr<hTaskBase>>::iterator, bool> ret;
			writeLk([&]() { ret = insert(pTask); });
			return ret;
		}

		PhTask hTaskMgrData::getTask(size_t tskId)
		{
			PhTask ret;
			readLk([&]() { ret = get(tskId); });
			return ret;
		}

		hTaskMgrData::hTaskMgrData(PWhTaskMgr pMgr) : 
			hTool::hUniqueIdGen<size_t, hTaskBase>(50),
			_pMgr(pMgr) { resize(10000, 99999); }

		size_t hWeightMgrData::getTaskAtRand()
		{
			std::vector<size_t> tIds;
			writeLk([&]() { getRandVal(tIds, 1); });
			if (tIds.empty())
				return 0;

			return tIds[0];
		}

		void hWeightMgrData::pushTask(size_t weight, size_t tskId)
		{
			if (!weight || !tskId)
			{
				COUT_LK(" 添加权重管理器失败，无效任务" << weight << "，" << tskId << "...");
				return;
			}

			writeLk([&]() { pushBack(weight, tskId); });
		}

		void hWeightMgrData::pushTask(PhTask pTask)
		{
			if (!pTask)
			{
				COUT_LK(" 添加权重管理器失败，空任务指针...");
				return;
			}

			pushTask(pTask->getWeight(), pTask->getId());
		}

		void hWeightMgrData::pushTask(PWhTask pTask)
		{
			if (!pTask)
			{
				COUT_LK(" 添加权重管理器失败，空任务指针...");
				return;
			}

			pushTask(pTask->getWeight(), pTask->getId());
		}

		hWeightMgrData::hWeightMgrData(PWhTaskMgr pMgr) :
			_pMgr(pMgr) {}

		bool hStatMgrData::updateState(size_t tskId, std::list<size_t>::iterator statIt,
			TaskStatType oldStat, TaskStatType newStat)
		{
			if (!tskId)
				return false;

			if (TaskStatType::Max <= oldStat)
				return false;

			if (TaskStatType::Max <= newStat)
				return false;

			if (oldStat == newStat)
				return false;

			writeLk([&]()
				{
					std::list<size_t>& oldList = _states[oldStat];
					std::list<size_t>& newList = _states[newStat];

					if (!statIt._Ptr || statIt == oldList.end())
						statIt = newList.insert(newList.end(), tskId);
					else
						newList.splice(newList.end(), oldList, statIt);
				});

			return true;
		}

		std::list<size_t>::iterator hStatMgrData::pushTask(PhTask pTask)
		{
			std::list<size_t>::iterator it;

			if (!pTask)
			{
				COUT_LK(" 添加状态管理器失败，空任务指针...");
				return it;
			}

			TaskStatType stat = pTask->getStat();
			if (!stat || stat >= TaskStatType::Max)
			{
				COUT_LK(pTask->getId() << " 添加状态管理器失败，异常状态" << stat.getName() <<"...");
				return it;
			}

			writeLk([&]() 
				{ 
					auto& stRef = _states[stat];
					auto rsState = stRef.insert(stRef.end(), pTask->getId());
					it = rsState;
				});

			return it;
		}

		hStatMgrData::hStatMgrData(PWhTaskMgr pMgr) :
			_pMgr(pMgr) {}

		void hUpdateMgrData::setId(size_t id)
		{
			if (!id)
			{
				COUT_LK(_pMgr->getName() << " 更新管理器id设置异常...");
				return;
			}


			writeLk([&]() { _updateId = id; });
		}

		size_t hUpdateMgrData::getId() const
		{
			size_t id = 0;
			readLk([&]() { id = _updateId; });
			return id;
		}


		hUpdateMgrData::hUpdateMgrData(PWhTaskMgr pMgr) :
			_pMgr(pMgr) {}
	}
}