#include "global.h"
#include "hRWLock.h"

namespace hThread
{
#define LOCK std::lock_guard<std::mutex> lk(m)

	bool hRWLock::readLock()
	{
		{
			LOCK;
			++rdCnt;
		}
		std::unique_lock<std::mutex> lk(rwM);
		rdCv.wait(lk, [&] { LOCK; return !wtCnt; });

		return true;
	}

	bool hRWLock::writeLock()
	{
		//rwM.lock();
		{
			LOCK;
			++wtCnt;

			if (rwM.try_lock())
				return true;
		}
		std::unique_lock<std::mutex> lk(wtM);
		wtCv.wait(lk, [&]
			{
				LOCK;

				if (!waiting)
				{
					waiting = true;
					return false;
				}
				if (!rwM.try_lock())
					return false;
				waiting = wtCnt - wtCnt ? 1 : 0;
				return true;
			});
		return true;
	}

	bool hRWLock::readUnlock()
	{
		{
			LOCK;
			rdCnt -= rdCnt ? 1 : 0;
			if (waiting)
				wtCv.notify_one();
		}

		return true;
	}

	bool hRWLock::writeUnlock()
	{
		{
			LOCK;
			wtCnt -= wtCnt ? 1 : 0;
			waiting = wtCnt;
			rwM.unlock();

			if (waiting)
				wtCv.notify_all();
			else if (rdCnt)
				rdCv.notify_all();
		}

		return true;
	}

#undef LOCK
}