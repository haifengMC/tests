#include <iostream>
#include <thread>
#include <chrono>

void foo()
{
	std::cout << "a thread\n";
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main()
{
	std::thread t1(foo);
	std::thread::id t1_id = t1.get_id();

	std::thread t2(foo);
	std::thread::id t2_id = t2.get_id();

	char buf[64] = "";
	sprintf_s(buf, "t1's id:  %d\n", t1_id);
	std::cout << buf;
	sprintf_s(buf, "t1's id:  %d\n", t2_id); 
	std::cout << buf;
	
	t1.join();
	t2.join();
}