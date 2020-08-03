#pragma once

namespace hThread
{
	class hRWLock
	{
	public:
		size_t rdCnt = 0;
		size_t wtCnt = 0;

		bool waiting = false;

		std::mutex m;//×ÔËø

		std::mutex rwM;//¶ÁÐ´Ëø
		std::mutex wtM;//Ð´µÈ´ýËø

		std::condition_variable rdCv;
		std::condition_variable wtCv;
	public:
		bool readLock();
		bool writeLock();

		bool readUnlock();
		bool writeUnlock();
	};
}