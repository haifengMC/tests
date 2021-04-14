#include "global.h"
#include "hThread.h"
#include "hPoolMgr.h"

namespace hThread
{
	hMemBase* createThrdMem(ThreadMemType t, size_t id)
	{
		switch (t)
		{
		case ThreadMemType::Work:
			return new hWorkMem(id);
		case ThreadMemType::Mgr:
			return new hMgrMem(id);
		default:
			break;
		}

		return NULL;
	}

	void hMemData::init(size_t num)
	{
		ThreadMemStatType stat = ThreadMemStatType::Init;
		for (size_t i = 0; i < num; ++i)
		{
			size_t id = _memArr.size();
			auto it = _thrdId[stat].insert(_thrdId[stat].end(), id);
			hMemBase* pMem = createThrdMem(_type, id);
			pMem->setStat(stat, it);
			_memArr.push_back(pMem);
		}
	}

	void hMemData::run()
	{
		execEvery(ThreadMemStatType::Init,
			[&](PhMemBase pMem) { pMem->run(); return true; });

		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	void hMemData::stop()
	{
		for (auto& mem : _memArr)
			mem->stop();
	}

	void hMemData::join()
	{
		for (auto& mem : _memArr)
			mem->join();
	}

	void hMemData::execEvery(ThreadMemStatType statTy,
		std::function<bool(PhMemBase)> func)
	{
		auto& thrdIds = _thrdId[statTy];
		for (auto it = thrdIds.begin(); it != thrdIds.end();)
		{
			auto pMem = _memArr[*it++];
			if (!pMem)
				continue;

			if (!func(pMem))
				break;
		}
	}

	hMemBase::hMemBase(size_t id) : _id(id) {}

	void hMemBase::run()
	{
		if (!updateStat(ThreadMemStatType::Wait))
			return;

		setFunc();
		_pThrd.bind(new std::thread(_func));
		//_pThrd->detach();
	}

	void hMemBase::stop()
	{
		if (!updateStat(ThreadMemStatType::Init))
			return;

		close();
		notify();
	}

	void hMemBase::join()
	{
		_pThrd->join();
	}

	bool hMemBase::setStat(ThreadMemStatType type, std::list<size_t>::iterator& it)
	{
		if (_statType == type)
			return false;

		if (ThreadMemStatType::Max <= type)
			return false;

		_statType = type;
		_statIt = it;
		return true;
	}

	bool hMemBase::updateStat(ThreadMemStatType type)
	{
		if (_statType == type)
			return false;

		if (ThreadMemStatType::Max <= type)
			return false;

		auto& data = shPool.getThrdMemData(_type);
		auto& oldList = data._thrdId[_statType];
		auto& newList = data._thrdId[type];

		_statType = type;
		newList.splice(newList.end(), oldList, _statIt);
		return true;
	}
}

