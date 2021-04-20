#pragma once

namespace hThread
{
	template<typename T>
	void hDataBase::readLk(T func)
	{
		if (!check())
		{
			checkErrOut();
			return;
		}

		rwLock.lock();
		func();
		rwLock.unlock();
	}

	template<typename T>
	void hDataBase::readLk(T func) const
	{
		if (!check())
		{
			checkErrOut();
			return;
		}

		rwLock.lock();
		func();
		rwLock.unlock();
	}

	template<typename T>
	void hDataBase::writeLk(T func)
	{
		if (!check())
		{
			checkErrOut();
			return;
		}

		rwLock.lock();
		func();
		rwLock.unlock();
	}

	template<typename T>
	void hDataBase::writeLk(T func) const
	{
		if (!check())
		{
			checkErrOut();
			return;
		}

		rwLock.lock();
		func();
		rwLock.unlock();
	}
}