//yield: 当前线程放弃执行，操作系统调度另一线程继续执行。
//线程让步。顾名思义，就是说当一个线程使用了这个方法之后，它就会把自己CPU执行的时间让掉，让自己或者其它的线程运行

#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>

// "busy sleep" while suggesting that other threads run 
// for a small amount of time
size_t gCnt = 0;
uint64_t totalElapsed = 0;
std::mutex elapsedMutex;

void little_sleep(int i, std::chrono::microseconds us)
{
	char buf[128] = "";

	auto start = std::chrono::high_resolution_clock::now();
	auto end = start + us;
	do {
		sprintf_s(buf, "yield %d\n", i);
		std::cout << buf;
		++gCnt;
		std::this_thread::yield();
	} while (std::chrono::high_resolution_clock::now() < end);

	uint64_t elapsed = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
	{
		std::lock_guard<std::mutex> lock(elapsedMutex);
		totalElapsed += elapsed;
	}

	sprintf_s(buf, "yield %d, elapsed=%llu\n", i, elapsed);
	std::cout << buf;
}

int main()
{
	auto start = std::chrono::high_resolution_clock::now();

	//little_sleep(std::chrono::microseconds(100));
	std::thread thArr[20];
	size_t cnt = 0;
	for (std::thread& th : thArr)
		th = std::thread(little_sleep, ++cnt, std::chrono::microseconds(50000));

	for (std::thread& th : thArr)
		th.join();

	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	std::cout << "waited for "
		<< std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count()
		<< " microseconds\n";
	std::cout << gCnt << " " << totalElapsed << std::endl;
}