#pragma once

namespace hThread
{
	struct hWLockIdType
	{
		enum _Value
		{
			Test,
			Max,
		};
	};

	//管理不同类型的写锁id，每个类型的写锁id，用于不同类型的读写锁
	class hWLockId
	{
		static std::mutex m;//自锁
		static uint64_t _id[hWLockIdType::Max];
	public:
		static uint64_t getId(size_t type);
		static uint64_t addId(size_t type);
	};

	class hRWLock
	{
		const size_t rwType = hWLockIdType::Max;//读写锁类型
		size_t rdCnt = 0;
		uint64_t wtId = 0;//写锁id

		bool writing = false;//在写入的写锁
		bool waiting = false;//在等待的写锁

		std::mutex m;//自锁

		std::mutex rwM;//读写锁
		std::mutex wtM;//写等待锁

		std::condition_variable rdCv;
		std::condition_variable wtCv;
	public:
		hRWLock(size_t rwType);

		bool readLock();
		bool readUnlock();
		bool writeLock(uint64_t id);
		bool writeUnlock();
	};

#if 0

	struct hRWLockData
	{
		const size_t rwType = hWLockIdType::Max;//读写锁类型
		bool error = false;	

		uint8_t rdCnt = 0;//0读锁数量
		uint64_t wtId = 0;//0写锁id
		bool waiting = false;//正在等待的0写锁
		bool writing = false;//正在写入的0写锁

		std::vector<uint8_t> itemRdCnt;//读锁数量
		std::vector<uint8_t> itemWaiting;//正在等待的写锁
		std::vector<uint8_t> itemWriting;//正在写入的写锁

		std::mutex m;//自锁

		std::mutex rwM;//读写锁
		std::mutex wtM;//写等待锁

		std::condition_variable rdCv;
		std::condition_variable wtCv;

		hRWLockData(size_t rwType);
	};

	class hRWLockItem
	{
	public:
		const uint8_t id = 0;

		hRWLockData& data;
		uint64_t wtId = 0;//写锁id

		std::mutex m;//自锁

		std::mutex rwM;//读写锁
		std::mutex wtM;//写等待锁

		std::condition_variable rdCv;
		std::condition_variable wtCv;
	public:
		hRWLockItem(uint8_t id, hRWLockData& data);

		bool readLock();
		bool readUnlock();

		bool writeLock(uint64_t id = 0);
		bool writeUnlock();
	private:
		bool tryLockRwM();
	};

	class hRWLockGroup
	{
	public:
		hRWLockData data;
		std::vector<uint8_t> none;//空值
		std::vector<hRWLockItem*> items;
	public:
		hRWLockGroup(size_t rwType, uint8_t n = 0);
		~hRWLockGroup();

		bool readLock(uint8_t i = 0);
		bool readUnlock(uint8_t i = 0);

		bool writeLock(uint8_t i = 0);
		bool writeUnlock(uint8_t i = 0);
	private:
		bool checkSize(uint8_t i);
		bool resize(uint8_t n);
	};
#endif
}