#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

timed_mutex g_mutex;

void f1()
{
	g_mutex.lock();
	cout << "f1" << endl;
	this_thread::sleep_for(chrono::seconds(2));
	g_mutex.unlock();
}

void f2()
{
	this_thread::sleep_for(chrono::seconds(1));

	g_mutex.lock();
	cout << "f2" << endl;
	g_mutex.unlock();
}

void f3()
{
	if (g_mutex.try_lock_for(chrono::seconds(1)))
	{
		cout << "f3" << endl;
		g_mutex.unlock();
	}
	else
	{
		g_mutex.lock();
		cout << "timeout" << endl;
		g_mutex.unlock();
	}
}

int main()
{
	thread t1(f1), t2(f2), t3(f3);

	t1.join();
	t2.join();
	t3.join();
}