#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex m;
std::condition_variable cv;
std::string data;
bool ready = false;
bool processed = false;
size_t workersCnt = 0;

void worker_thread(int i)
{
	// 等待直至 main() 发送数据
	std::unique_lock<std::mutex> lk(m);
	cv.wait(lk, [] {return ready; });

	// 等待后，我们占有锁。
	std::cout << "Worker" << i << " thread is processing data\n";
	data += std::to_string(i) += " after processing ";

	// 发送数据回 main()
	if (workersCnt <= 1)
	{
		processed = true;
		std::cout << "Worker thread signals data processing completed\n";
	}
	else --workersCnt;

	// 通知前完成手动解锁，以避免等待线程才被唤醒就阻塞（细节见 notify_one ）
	lk.unlock();
	cv.notify_one();
}

int main()
{
	std::thread worker1(worker_thread, 1);
	std::thread worker2(worker_thread, 2);
	data = "Example data ";
	workersCnt = 2;
	// 发送数据到 worker 线程
	{
		std::lock_guard<std::mutex> lk(m);
		ready = true;
		std::cout << "main() signals data ready for processing\n";
	}
	cv.notify_one();

	// 等候 worker
	{
		std::unique_lock<std::mutex> lk(m);
		cv.wait(lk, [] {return processed; });
	}
	std::cout << "Back in main(), data = " << data << '\n';

	worker1.join();
	worker2.join();
}