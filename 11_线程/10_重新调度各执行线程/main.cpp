//yield: 当前线程放弃执行，操作系统调度另一线程继续执行。
//线程让步。顾名思义，就是说当一个线程使用了这个方法之后，它就会把自己CPU执行的时间让掉，让自己或者其它的线程运行

#include <iostream>
#include <chrono>
#include <thread>

// "busy sleep" while suggesting that other threads run 
// for a small amount of time
void little_sleep(std::chrono::microseconds us)
{
	auto start = std::chrono::high_resolution_clock::now();
	auto end = start + us;
	do {
		std::cout << "start yield " << std::this_thread::get_id() << std::endl;
		//std::this_thread::yield();
	} while (std::chrono::high_resolution_clock::now() < end);
}

int main()
{
	auto start = std::chrono::high_resolution_clock::now();

	little_sleep(std::chrono::microseconds(100));

	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	std::cout << "waited for "
		<< std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count()
		<< " microseconds\n";
}