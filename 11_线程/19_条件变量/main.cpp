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
	// �ȴ�ֱ�� main() ��������
	std::unique_lock<std::mutex> lk(m);
	cv.wait(lk, [] {return ready; });

	// �ȴ�������ռ������
	std::cout << "Worker" << i << " thread is processing data\n";
	data += std::to_string(i) += " after processing ";

	// �������ݻ� main()
	if (workersCnt <= 1)
	{
		processed = true;
		std::cout << "Worker thread signals data processing completed\n";
	}
	else --workersCnt;

	// ֪ͨǰ����ֶ��������Ա���ȴ��̲߳ű����Ѿ�������ϸ�ڼ� notify_one ��
	lk.unlock();
	cv.notify_one();
}

int main()
{
	std::thread worker1(worker_thread, 1);
	std::thread worker2(worker_thread, 2);
	data = "Example data ";
	workersCnt = 2;
	// �������ݵ� worker �߳�
	{
		std::lock_guard<std::mutex> lk(m);
		ready = true;
		std::cout << "main() signals data ready for processing\n";
	}
	cv.notify_one();

	// �Ⱥ� worker
	{
		std::unique_lock<std::mutex> lk(m);
		cv.wait(lk, [] {return processed; });
	}
	std::cout << "Back in main(), data = " << data << '\n';

	worker1.join();
	worker2.join();
}