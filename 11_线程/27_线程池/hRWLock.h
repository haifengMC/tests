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
		const size_t rwType = hWLockIdType::Max;//��д������
		size_t rdCnt = 0;
		uint64_t wtId = 0;//д��id

		bool writing = false;//��д���д��
		bool waiting = false;//�ڵȴ���д��

		std::mutex m;//����

		std::mutex rwM;//��д��
		std::mutex wtM;//д�ȴ���

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
		const size_t rwType = hWLockIdType::Max;//��д������
		bool error = false;	

		uint8_t rdCnt = 0;//0��������
		uint64_t wtId = 0;//0д��id
		bool waiting = false;//���ڵȴ���0д��
		bool writing = false;//����д���0д��

		std::vector<uint8_t> itemRdCnt;//��������
		std::vector<uint8_t> itemWaiting;//���ڵȴ���д��
		std::vector<uint8_t> itemWriting;//����д���д��

		std::mutex m;//����

		std::mutex rwM;//��д��
		std::mutex wtM;//д�ȴ���

		std::condition_variable rdCv;
		std::condition_variable wtCv;

		hRWLockData(size_t rwType);
	};

	class hRWLockItem
	{
	public:
		const uint8_t id = 0;

		hRWLockData& data;
		uint64_t wtId = 0;//д��id

		std::mutex m;//����

		std::mutex rwM;//��д��
		std::mutex wtM;//д�ȴ���

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
		std::vector<uint8_t> none;//��ֵ
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