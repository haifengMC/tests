#include <iostream>
#include <utility>
#include <thread>
#include <chrono>
#include <functional>
#include <atomic>

using namespace std;

void f1(int n)
{
	for (int i = 0; i < 3; ++i)
	{
		char buf[64] = "";
		sprintf_s(buf, "Thread f1 %d executing\n", n);
		cout << buf;
		this_thread::sleep_for(std::chrono::seconds(3));
	}
}

void f2(int& n)
{
	for (int i = 0; i < 4; ++i) 
	{
		char buf[64] = "";
		sprintf_s(buf, "Thread f2 %d executing\n", n);
		cout << buf;
		++n;
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}
}

int main()
{
	int n = 0;
	std::thread t1; // t1 is not a thread
	std::thread t2(f1, n + 1); // pass by value
	std::thread t3(f2, std::ref(n)); // pass by reference
	std::thread t4(std::move(t3)); // t4 is now running f2(). t3 is no longer a thread
	t2.join();
	t4.join();
	std::cout << "Final value of n is " << n << '\n';
}