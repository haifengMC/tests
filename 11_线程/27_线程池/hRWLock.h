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
	public:
		const size_t rwType = hWLockIdType::Max;//读写锁类型

		size_t rdCnt = 0;
		uint64_t wtId = 0;//写锁id

		bool waiting = false;
		bool writing = false;
		bool error = false;

		std::mutex m;//自锁

		std::mutex rwM;//读写锁
		std::mutex wtM;//写等待锁

		std::condition_variable rdCv;
		std::condition_variable wtCv;
	public:
		hRWLock(size_t rwType);

		bool readLock();
		bool writeLock(uint64_t id = 0);

		bool readUnlock();
		bool writeUnlock();
	};
}