#pragma once


class hRWLock
{
public:
	size_t rdCnt = 0;
	size_t wtCnt = 0;

	bool writing = false;

	std::mutex m;//����

	std::mutex rwM;//��д��
	std::mutex wtM;//д�ȴ���

	std::condition_variable rdCv;
	std::condition_variable wtCv;
public:

	bool readLock();
	bool readUnlock();
	bool writeLock();
	bool writeUnlock();

};