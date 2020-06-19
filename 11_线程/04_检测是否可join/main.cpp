//join: Join 线程，调用该函数会阻塞当前线程，直到由* this 所标示的线程执行完毕 join 才返回。
#include <iostream>
#include <thread>
#include <chrono>

void foo()
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main()
{
	std::thread t;
	std::cout << "before starting, joinable: " << t.joinable() << '\n';

	t = std::thread(foo);
	std::cout << "after starting, joinable: " << t.joinable() << '\n';

	t.join();
}