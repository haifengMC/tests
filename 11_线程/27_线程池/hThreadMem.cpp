#include "global.h"
#include "hThread.h"
#include "hThreadPoolMgr.h"

namespace hThread
{
	ThreadMem* createThrdMem(ThreadMemType t, size_t id)
	{
		switch (t)
		{
		case ThreadMemType::Work:
			return new ThreadMemWork(id);
		case ThreadMemType::Mgr:
			return new ThreadMemMgr(id);
		default:
			break;
		}

		return NULL;
	}

	ThreadMem::ThreadMem(size_t id) : _id(id) {}

	void ThreadMem::run()
	{
		if (!updateStat(ThreadMemStatType::Wait))
			return;

		setFunc();
		_pThrd.bind(new std::thread(_func));
		//_pThrd->detach();
	}

	void ThreadMem::stop()
	{
		if (!updateStat(ThreadMemStatType::Init))
			return;

		close();
		notify();
	}

	void ThreadMem::join()
	{
		_pThrd->join();
	}

	bool ThreadMem::setStat(ThreadMemStatType type, std::list<size_t>::iterator& it)
	{
		if (_statType == type)
			return false;

		if (ThreadMemStatType::Max <= type)
			return false;

		_statType = type;
		_statIt = it;
		return true;
	}

	bool ThreadMem::updateStat(ThreadMemStatType type)
	{
		if (_statType == type)
			return false;

		if (ThreadMemStatType::Max <= type)
			return false;

		auto& data = sThrdPool.getThrdMemData(_type);
		auto& oldList = data._thrdId[_statType];
		auto& newList = data._thrdId[type];

		_statType = type;
		newList.splice(newList.end(), oldList, _statIt);
		return true;
	}
}

