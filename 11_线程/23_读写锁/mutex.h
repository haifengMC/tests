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

	std::mutex m;

	std::mutex rdM;
	std::mutex wtM;
	std::mutex rwM;

	std::condition_variable rdCv;
	std::condition_variable wt1Cv;
	std::condition_variable wt2Cv;
public:
	bool read_lock();
	bool write_lock();

	bool read_unlock();
	bool write_unlock();
};