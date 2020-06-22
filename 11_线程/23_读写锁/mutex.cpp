#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include "mutex.h"

#define LOCK std::lock_guard<std::mutex> lk(m)

bool read_write_mutex::read_lock()
{
	{
		LOCK;
		++rdCnt;
	}
	std::unique_lock<std::mutex> lk(rwM);
	rdCv.wait(lk, [&] { LOCK; return !wtCnt; });

	return true;
}

bool read_write_mutex::write_lock()
{
	//rwM.lock();
	{
		LOCK;
		++wtCnt;
		if (rwM.try_lock())
		{
			isWriting = true;
			return true;
		}
	}
	bool ret = true;
	std::unique_lock<std::mutex> lk(wtM);
	wtCv.wait(lk, [&]
		{ 
			LOCK;
			if (isDiscard)
			{
				wtCnt -= wtCnt ? 1 : 0;
				isDiscard = false;
				ret = false;
				return true;
			}

			if (!isWaiting)
			{
				isWaiting = true;
				return false;
			}

			if (!isWriting && rwM.try_lock())
			{
				isWriting = true;
				isWaiting = false;
				return true;
			}

			isDiscard = true;
			wtCv.notify_one();
			return false;
		});
	return ret;
}

bool read_write_mutex::read_unlock()
{
	{
		LOCK;
		rdCnt -= rdCnt ? 1 : 0;
		if (isWaiting)
			wtCv.notify_one();
	}

	return true;
}

bool read_write_mutex::write_unlock()
{
	{
		LOCK;
		wtCnt -= wtCnt ? 1 : 0;
		isWriting = false;

		rwM.unlock();

		if (isWaiting)
			wtCv.notify_one();
		if (rdCnt)
			rdCv.notify_all();
	}

	return true;
}
