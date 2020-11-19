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

	//����ͬ���͵�д��id��ÿ�����͵�д��id�����ڲ�ͬ���͵Ķ�д��
	class hWLockId
	{
		static std::mutex m;//����
		static uint64_t _id[hWLockIdType::Max];
	public:
		static uint64_t getId(size_t type);
		static uint64_t addId(size_t type);
	};

	class hRWLock
	{
	public:
		const size_t rwType = hWLockIdType::Max;//��д������

		size_t rdCnt = 0;
		uint64_t wtId = 0;//д��id

		bool waiting = false;
		bool writing = false;
		bool error = false;

		std::mutex m;//����

		std::mutex rwM;//��д��
		std::mutex wtM;//д�ȴ���

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