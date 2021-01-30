#include "global.h"
#include "hRWLock.h"

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

bool hRWLock::readUnlock()
{
	{
		LOCK;
		rdCnt -= rdCnt ? 1 : 0;
		if (wtCnt)
			wtCv.notify_one();
	}

	return true;
}

bool hRWLock::writeLock()
{
	{
		LOCK;
		++wtCnt;

		if (rwM.try_lock())
		{
			writing = true;
			return true;
		}
	}
	std::unique_lock<std::mutex> lk(wtM);
	wtCv.wait(lk, [&]
		{
			LOCK;

			if (writing)
				return false;

			if (!rwM.try_lock())
			{
				wtCv.notify_one();
				return false;
			}

			writing = true;
			return true;
		});
	return true;
}

bool hRWLock::writeUnlock()
{
	{
		LOCK;
		wtCnt -= wtCnt ? 1 : 0;
		writing = false;
		rwM.unlock();

		if (wtCnt)
			wtCv.notify_one();
		else if (rdCnt)
			rdCv.notify_all();
	}

	return true;
}
#undef LOCK