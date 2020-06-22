#pragma once

namespace std
{
	class mutex;
	class condition_variable;
}

class read_write_mutex
{
public:
	size_t rdCnt = 0;
	size_t wtCnt = 0;

	bool isDiscard = false;
	bool isWriting = false;
	bool isWaiting = false;

	std::mutex m;//����

	std::mutex rwM;//��д��
	std::mutex wtM;//д�ȴ���

	std::condition_variable rdCv;
	std::condition_variable wtCv;
public:
	bool read_lock();
	bool write_lock();

	bool read_unlock();
	bool write_unlock();
};