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

		pRWLock->lock();
		func();
		pRWLock->unlock();
	}

	template<typename T>
	void hDataBase::readLk(T func) const
	{
		if (!check())
		{
			checkErrOut();
			return;
		}

		pRWLock->lock();
		func();
		pRWLock->unlock();
	}

	template<typename T>
	void hDataBase::writeLk(T func)
	{
		if (!check())
		{
			checkErrOut();
			return;
		}

		pRWLock->lock();
		func();
		pRWLock->unlock();
	}

	template<typename T>
	void hDataBase::writeLk(T func) const
	{
		if (!check())
		{
			checkErrOut();
			return;
		}

		pRWLock->lock();
		func();
		pRWLock->unlock();
	}
}