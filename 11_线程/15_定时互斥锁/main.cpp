#include <thread>
#include <iostream>
#include <chrono>
#include <mutex>

std::timed_mutex test_mutex;

void f()
{
	auto now = std::chrono::steady_clock::now();
	if (test_mutex.try_lock_until(now + std::chrono::seconds(3)))
		std::cout << "hello world\n";
	else
		std::cout << "failed!" << std::endl;
}

int main()
{
	std::lock_guard<std::timed_mutex> l(test_mutex);
	std::thread t(f);
	t.join();
}