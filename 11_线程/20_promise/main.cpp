#include <vector>
#include <thread>
#include <future>
#include <numeric>
#include <iostream>
#include <chrono>
#include <mutex>

std::mutex cout_mutex;
#define OUT_LOCK std::lock_guard<std::mutex> lock(cout_mutex)

void accumulate(std::vector<int>::iterator first,
	std::vector<int>::iterator last,
	std::promise<int> accumulate_promise)
{
	int sum = std::accumulate(first, last, 0);
	{
		OUT_LOCK;
		std::cout << "set_value" << std::endl;
	}

	std::this_thread::sleep_for(std::chrono::seconds(1));

	accumulate_promise.set_value(sum);  // ���� future

	std::this_thread::sleep_for(std::chrono::seconds(1));
	{
		OUT_LOCK;
		std::cout << "set_value complete" << std::endl;
	}

	std::this_thread::sleep_for(std::chrono::seconds(1));
	{
		OUT_LOCK;
		std::cout << "exit_thread" << std::endl;
	}
}

void do_work(std::promise<void> barrier)
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
	barrier.set_value();
}

int main()
{
	// ��ʾ�� promise<int> ���̼߳䴫�ݽ����
	std::vector<int> numbers = { 1, 2, 3, 4, 5, 6 };
	std::promise<int> accumulate_promise;
	std::future<int> accumulate_future = accumulate_promise.get_future();
	std::thread work_thread(accumulate, numbers.begin(), numbers.end(),
		std::move(accumulate_promise));

	// future::get() ���ȴ�ֱ���� future ӵ�кϷ������ȡ����
	// ������ get() ǰ���� wait()
	//accumulate_future.wait();  // �ȴ����
	int result = accumulate_future.get();
	{
		OUT_LOCK;
		std::cout << "result=" << result << std::endl;
	}

	work_thread.join();  // wait for thread completion

	// ��ʾ�� promise<void> ���̼߳��״̬���ź�
	std::promise<void> barrier;
	std::future<void> barrier_future = barrier.get_future();
	std::thread new_work_thread(do_work, std::move(barrier));
	barrier_future.wait();
	new_work_thread.join();
}