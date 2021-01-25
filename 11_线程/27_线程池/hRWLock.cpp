#include "global.h"
#include "hRWLock.h"

namespace hThread
{
#define LOCK0 std::lock_guard<std::mutex> lk(data.m)
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

	hRWLock::hRWLock(size_t rwType)
	{
		if (rwType >= hWLockIdType::Max)
			throw std::range_error("读写锁类型异常");
	}

	bool hRWLock::readLock()
	{
		{
			LOCK;
			++rdCnt;
#ifdef _D_RWLOCK
			std::cout << "readLock加读锁 rdCnt:" << rdCnt << std::endl;
#endif
		}
		std::unique_lock<std::mutex> lk(rwM);
		rdCv.wait(lk, [&] 
			{
				LOCK;
#ifdef _D_RWLOCK
				std::cout << "readLock没有写锁等待和写入时读取 writing:" << writing << " waiting:" << waiting << std::endl;
#endif
				return !writing && !waiting; });

		return true;
	}

	bool hRWLock::readUnlock()
	{
		{
			LOCK;
			rdCnt -= rdCnt ? 1 : 0;
			if (waiting)
				wtCv.notify_all();
#ifdef _D_RWLOCK
			std::cout << "readUnlock减读锁，写锁等待时通知 rdCnt:" << rdCnt << " waiting:" << waiting << std::endl;
#endif
		}

		return true;
	}

	bool hRWLock::writeLock(uint64_t id)
	{
		{
			LOCK;

			if (wtId >= id)
				return false;//丢弃旧写锁

#ifdef _D_RWLOCK
			std::cout << "writeLock加写锁 oldId:" << wtId << " newId:" << id << std::endl;
#endif
			wtId = id;
			//如果加锁成功则写入
			if (rwM.try_lock())
			{
				writing = true;
#ifdef _D_RWLOCK
				std::cout << "writeLock加锁成功时写入1 wtId:" << wtId << std::endl;
#endif
				return true;
			}
		}

		bool ret = true;
		std::unique_lock<std::mutex> lk(wtM);
		wtCv.wait(lk, [&]
			{
				LOCK;
				if (wtId > id)
				{//丢弃旧写锁
					ret = false;
#ifdef _D_RWLOCK
					std::cout << "writeLock丢弃旧写锁 oldId:" << id << "newId:" << wtId << std::endl;
#endif
					return true;
				}

				if (waiting)
				{//标记为等待则丢弃其他等待线程
					wtCv.notify_all();
#ifdef _D_RWLOCK
					std::cout << "writeLock标记为等待则丢弃其他等待线程" << std::endl;
#endif
					return false;
				}

				if (writing)
				{//写入时等待
					waiting = true;
#ifdef _D_RWLOCK
					std::cout << "writeLock有写入时等待" << std::endl;
#endif
					return false;
				}

				if (rwM.try_lock())
				{//加锁成功时写入
					writing = true;
#ifdef _D_RWLOCK
					std::cout << "writeLock加锁成功时写入2 wtId:" << wtId << std::endl;
#endif
					return true;
				}

				//读等待
				waiting = true;
#ifdef _D_RWLOCK
				std::cout << "writeLock有读锁读取时等待" << std::endl;
#endif
				return false;
			});
		return ret;
	}

	bool hRWLock::writeUnlock()
	{
		LOCK;
		writing = false;
		rwM.unlock();

		if (waiting)
		{
			waiting = false;
			wtCv.notify_all();
#ifdef _D_RWLOCK
			std::cout << "writeUnlock减写锁通知等待写锁" << std::endl;
#endif
			return true;
		}

		if (rdCnt)
			rdCv.notify_all();

#ifdef _D_RWLOCK
		std::cout << "writeUnlock减写锁有读锁则通知 rdCnt:" << rdCnt << std::endl;
#endif
		return true;
	}
#undef LOCK

#if 0
	hRWLockData::hRWLockData(size_t rwType) : rwType(rwType)
	{
		if (rwType >= hWLockIdType::Max)
			error = true;
	}

	hRWLockItem::hRWLockItem(uint8_t id, hRWLockData& data) :
		id(id), data(data) {}

	bool hRWLockItem::readLock()
	{
		std::unique_lock<std::mutex> lk(rwM);

		//读等待上限后等待
		rdCv.wait(lk, [&]
			{
				LOCK;
				return data.itemRdCnt[id] < (uint8_t)-1;
			});

		{
			LOCK;
			++data.itemRdCnt[id];
		}

		//没有写入时读取
		rdCv.wait(lk, [&] 
			{ 
				LOCK0;
				LOCK;
				return 
					!data.waiting &&
					!data.writing &&
					!data.itemWaiting[id] && 
					!data.itemWriting[id]; 
			});

		return true;
	}

	bool hRWLockItem::readUnlock()
	{
		{
			LOCK;
			data.itemRdCnt[id] -= data.itemRdCnt[id] ? 1 : 0;
		}
			
		{
			LOCK0;
			if (data.waiting)//如果有等待的0写锁则通知
			{
				data.wtCv.notify_one();
				return true;
			}
		}

		{
			LOCK;
			if (data.itemWaiting[id])//如果自己有写等待则通知
			{
				wtCv.notify_one();
				return true;
			}
		}

		return true;
	}

	bool hRWLockItem::writeLock(uint64_t id)
	{
		{
			LOCK0;
			if (data.wtId >= id)
				return false;//丢弃旧写锁
		}

		{
			LOCK;

			if (wtId >= id)
				return false;//丢弃旧写锁

			wtId = id;

			//如果加锁成功则写入
			if (tryLockRwM())
			{
				data.itemWriting[id] = 1;
				return true;
			}
		
		}
		bool ret = true;
		std::unique_lock<std::mutex> lk(wtM);
		wtCv.wait(lk, [&]
			{
				bool writing = false;

				{
					LOCK0;
					if (data.wtId > id)
					{//丢弃旧写锁
						ret = false;
						return true;
					}

					if (data.waiting)//0写锁等待时其他写锁也等待
						return false;

					writing = data.writing;
				}

				{
					LOCK;
					if (wtId > id)
					{//丢弃旧写锁
						ret = false;
						return true;
					}

					if (data.itemWaiting[id])
					{//标记为等待则丢弃其他等待线程
						wtCv.notify_all();
						return false;
					}

					if (data.itemWriting[id])
					{//写入时等待
						data.itemWaiting[id] = 1;
						return false;
					}

					if (tryLockRwM())
					{//加锁成功时写入
						data.itemWriting[id] = 1;
						return true;
					}

					//读等待
					data.itemWaiting[id] = 1;
					return false;
				}
			});
		return ret;
	}

	bool hRWLockItem::writeUnlock()
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

	bool hRWLockItem::tryLockRwM()
	{
		if (data.rwM.try_lock())
		{
			if (rwM.try_lock())
				return true;
			else
				data.rwM.unlock();
		}

		return false;
	}

	hRWLockGroup::hRWLockGroup(size_t rwType, uint8_t n = 0) : data(rwType)
	{
		if (data.error)
			return;

		if (!n)
			return;

		resize(n);
	}

	hRWLockGroup::~hRWLockGroup()
	{
		for (auto p : items)
			delete p;
	}

	bool hRWLockGroup::readLock(uint8_t i)
	{
		if (!checkSize(i))
			return false;

		if (i)
			return items[i - 1]->readLock();

		std::unique_lock<std::mutex> lk(data.rwM);	

		//读等待上限后等待
		data.rdCv.wait(lk, [&]
			{
				LOCK0;
				return data.rdCnt < (uint8_t)-1;
			});

		{
			LOCK0;
			++data.rdCnt;
		}

		//没有写入时读取
		data.rdCv.wait(lk, [&] 
			{
				LOCK0; 
				return 
					!data.waiting &&
					!data.writing &&
					data.itemWaiting == none && 
					data.itemWriting == none; 
			});

		return true;
	}

	bool hRWLockGroup::readUnlock(uint8_t i)
	{
		if (i >= items.size())
			return false;

		if (i)
			return items[i - 1]->readUnlock();

		LOCK0;
		data.rdCnt -= data.rdCnt ? 1 : 0;
		if (data.waiting)//如果有等待的0写锁则通知
		{
			data.wtCv.notify_one();
			return true;
		}

		if (data.itemWaiting == none)//如果没有等待写锁直接返回
			return true;

		//通知所有在等待的写锁
		for (uint8_t id = 0; id < data.itemWaiting.size(); ++id)
		{
			if (!data.itemWaiting[id])
				continue;

			items[id]->wtCv.notify_one();
		}

		return true;
	}

	bool hRWLockGroup::writeLock(uint8_t i)
	{
		if (!checkSize(i))
			return false;

		uint64_t id = hWLockId::addId(data.rwType);
		if (!id)
			return false;

		if (i)
			return items[i - 1]->writeLock(id);

		{
			LOCK;

			if (data.wtId >= id)
				return false;//丢弃旧写锁

			data.wtId = id;


			if (rwM.try_lock())//如果加锁成功则写入
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
				{//丢弃旧写锁
					ret = false;
					return true;
				}

				if (waiting)
				{//标记为等待则丢弃其他等待线程
					wtCv.notify_all();
					return false;
				}

				if (writing)
				{//写入时等待
					waiting = true;
					return false;
				}

				if (rwM.try_lock())
				{//加锁成功时写入
					writing = true;
					return true;
				}

				waiting = true;
				return false;
			});
		return ret;
	}

	bool hRWLockGroup::writeUnlock(uint8_t i)
	{
		return false;
	}

	bool hRWLockGroup::checkSize(uint8_t i)
	{
		if (data.error)
			return false;

		if (i > items.size())
			return resize(i);

		return true;
	}

	bool hRWLockGroup::resize(uint8_t n)
	{
		LOCK0;

		if (data.error)
			return false;

		uint8_t cnt = items.size();
		if (n == cnt)
			return true;

		if (n < cnt)
			for (uint8_t i = n; i < cnt; ++i)
				delete items[i];

		items.resize(n);
		data.itemRdCnt.resize(n);
		data.itemWaiting.resize(n);
		data.itemWriting.resize(n);
		none.resize(n);

		if (n > cnt)
			for (uint8_t i = cnt; i < n; ++i)
				items[i] = new hRWLockItem(i, data);
	}
#endif

#undef LOCK
#undef LOCK0
}