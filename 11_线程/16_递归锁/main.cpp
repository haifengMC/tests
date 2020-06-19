#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

recursive_mutex g_mutex;

void f2(int = 0);
void f1(int i = 0)
{
	lock_guard<recursive_mutex> lock(g_mutex);
	cout << "f1: " << this_thread::get_id() << endl;
	if (i) f2();
}

void f2(int i)
{
	lock_guard<recursive_mutex> lock(g_mutex);
	cout << "f2: " << this_thread::get_id() << endl;
	if (i) f1();
}

int main()
{
	thread t1(f1, 1), t2(f2, 1);
	t1.join();
	t2.join();


	return 0;
}