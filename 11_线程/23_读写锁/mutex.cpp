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
	{
		LOCK;
		++wtCnt;
	}
	rwM.lock();

	return true;
}

bool read_write_mutex::read_unlock()
{
	{
		LOCK;
		rdCnt -= rdCnt ? 1 : 0;
	}

	return true;
}

bool read_write_mutex::write_unlock()
{
	{
		LOCK;
		wtCnt -= wtCnt ? 1 : 0;
	}
	rwM.unlock();
	if (rdCnt)
		rdCv.notify_all();
	return true;
}
