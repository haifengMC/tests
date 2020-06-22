#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>

#include "mutex.h"

using namespace std;

string s = "hello";
read_write_mutex m;
mutex coutM;

#define COUT_LOCK(x) { lock_guard<mutex> lk(coutM); cout << "[" << this_thread::get_id() << "]" << #x << endl; }
void readFunc()
{

	COUT_LOCK(read lock);
	m.read_lock();

	COUT_LOCK(read)

	m.read_unlock();
	COUT_LOCK(read unlock)
}

void writeFunc()
{

	COUT_LOCK(write lock);

	if (m.write_lock())
	{
		std::this_thread::sleep_for(chrono::seconds(1));

		COUT_LOCK(write success);

		m.write_unlock();
		COUT_LOCK(write unlock);
	}
	else
		COUT_LOCK(write failed);

}

int main()
{
	vector<thread> rwVec;
	for (int i = 1; i <= 10; ++i)
		rwVec.emplace_back(readFunc);
	vector<thread> wtVec;
	for (int i = 1; i <= 10; ++i)
		wtVec.emplace_back(writeFunc);
	
	for (thread& thd : rwVec)
		thd.join();
	for (thread& thd : wtVec)
		thd.join();

	return 0;
}