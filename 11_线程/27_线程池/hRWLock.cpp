#include "global.h"
#include "hRWLock.h"

namespace hThread
{
#define LOCK std::lock_guard<std::mutex> lk(m)

	std::mutex hWLockId::m;
	uint64_t hWLockId::_id[hWLockIdType::Max];

	uint64_t hWLockId::getId(size_t type)
	{
		LOCK;
		if (hWLockIdType::Max <= type)
			return 0;

		return _id[type];
	}

	uint64_t hWLockId::addId(size_t type)
	{
		LOCK;
		if (hWLockIdType::Max <= type)
			return 0;

		return ++_id[type];
	}

	hRWLock::hRWLock(size_t rwType) : rwType(rwType)
	{
		if (rwType >= hWLockIdType::Max)
			error = true;
	}

	bool hRWLock::readLock()
	{
		{
			LOCK;
			if (error) 
				return false;

			++rdCnt;
		}
		std::unique_lock<std::mutex> lk(rwM);
		//û��д��ʱ��ȡ
		rdCv.wait(lk, [&] { LOCK; return !waiting && !writing; });

		return true;
	}

	bool hRWLock::writeLock(uint64_t id)
	{
		{
			LOCK;
			if (error)
				return false;

			if (id > hWLockId::getId(rwType))
				return false;//����Ƿ�id

			if (wtId >= id)
				return false;//������д��

			wtId = id;
			if (rwM.try_lock())//��������ɹ���д��
			{
				writing = true;
				return true;
			}
		}
		bool ret = true;
		std::unique_lock<std::mutex> lk(wtM);
		wtCv.wait(lk, [&]
			{
				LOCK;

				if (wtId > id)
				{//������д��
					ret = false;
					return true;
				}

				if (waiting)
				{//���Ϊ�ȴ����������ȴ��߳�
					wtCv.notify_all();
					return false;
				}

				if (writing)
				{//д��ʱ�ȴ�
					waiting = true;
					return false;
				}

				if (rwM.try_lock())
				{//�����ɹ�ʱд��
					writing = true;
					return true;
				}

				waiting = true;
				return false;
			});
		return ret;
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
			writing = false;
			rwM.unlock();

			if (waiting)
			{
				wtCv.notify_all();
				waiting = false;
				return true;
			}
			
			if (rdCnt)
				rdCv.notify_all();
		}

		return true;
	}

#undef LOCK
}