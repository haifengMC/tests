#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

struct Box {
	explicit Box(int num) : num_things{ num } {}

	int num_things;
	std::mutex m;
};

void transfer(Box& from, Box& to, int num)
{
	// ��δʵ��ȡ��
	std::unique_lock<std::mutex> lock1(from.m, std::defer_lock);
	std::unique_lock<std::mutex> lock2(to.m, std::defer_lock);

	// ������ unique_lock ��������
	std::lock(lock1, lock2);

	from.num_things -= num;
	to.num_things += num;

	std::cout << "from" << from.num_things << " to" << to.num_things << " trans" << num << std::endl;

	// 'from.m' �� 'to.m' ��������� 'unique_lock' ��������
}

int main()
{
	Box acc1(100);
	Box acc2(50);

	std::thread t1(transfer, std::ref(acc1), std::ref(acc2), 10);
	std::thread t2(transfer, std::ref(acc2), std::ref(acc1), 5);

	t1.join();
	t2.join();
}