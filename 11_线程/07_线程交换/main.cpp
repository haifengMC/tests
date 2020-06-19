//swap: Swap 线程，交换两个线程对象所代表的底层句柄(underlying handles)。
#include <iostream>
#include <thread>
#include <chrono>

void foo()
{
	for (int i = 0; i < 7; ++i)
	{
		char buf[64] = "";
		char format[] = "thread %s id: %d\n";
		sprintf_s(buf, format, "foo", std::this_thread::get_id());
		std::cout << buf;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

void bar()
{
	for (int i = 0; i < 7; ++i)
	{
		char buf[64] = "";
		char format[] = "thread %s id: %d\n";
		sprintf_s(buf, format, "bar", std::this_thread::get_id());
		std::cout << buf;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

int main()
{
	char buf[64] = "";
	char format[] = "thread %d id: %d\n";
	std::thread t1(foo);
	std::thread t2(bar);

	sprintf_s(buf, format, 1, t1.get_id());
	std::cout << buf;
	sprintf_s(buf, format, 2, t2.get_id());
	std::cout << buf;

	std::this_thread::sleep_for(std::chrono::seconds(2));
	std::swap(t1, t2);

	std::cout << "after std::swap(t1, t2):" << std::endl;

	sprintf_s(buf, format, 1, t1.get_id());
	std::cout << buf;
	sprintf_s(buf, format, 2, t2.get_id());
	std::cout << buf;

	std::this_thread::sleep_for(std::chrono::seconds(2));
	t1.swap(t2);

	std::cout << "after t1.swap(t2):" << std::endl;

	sprintf_s(buf, format, 1, t1.get_id());
	std::cout << buf;
	sprintf_s(buf, format, 2, t2.get_id());
	std::cout << buf;

	t1.join();
	t2.join();
}