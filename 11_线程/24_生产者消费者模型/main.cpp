#include <iostream>
#include <vector>

#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

#define LOCK lock_guard<mutex> lk(m)

class Manager
{
public:
	size_t producer = 0, consumer = 0, product = 0, productMax = 0;
	mutex m, cvM;
	condition_variable cvPdcr, cvCsmr;

	vector<thread> pdcrThd, csmrThd;
public:
	Manager(const size_t& producer, const size_t& consumer, const size_t& productMax);
	void join();
};
Manager::Manager(const size_t& producer, const size_t& consumer, const size_t& productMax) :
	producer(producer), consumer(consumer), productMax(productMax)
{
	auto produce = [&]
	{
		for (size_t i = 0; i < 10; ++i)
		{
			this_thread::sleep_for(chrono::seconds(3));
			{
				LOCK;
				cout << "wait product " << product << endl;
			}
			std::unique_lock<std::mutex> lk(cvM);
			cvPdcr.wait(lk, [&] { return product < productMax; });
			{
				LOCK;
				++product;
				cvCsmr.notify_all();
				cout << "product " << product << endl;
			}
		}

		{
			LOCK;
			cout << "product finish" << endl;
		}
	};
	for (size_t i = 0; i < producer; ++i)
		pdcrThd.emplace_back(produce);
	auto consume = [&]
	{
		for (size_t i = 0; i < 10; ++i)
		{
			this_thread::sleep_for(chrono::seconds(2));
			{
				LOCK;
				cout << "wait consume " << product << endl;
			}
			std::unique_lock<std::mutex> lk(cvM);
			cvCsmr.wait(lk, [&] { return product; });
			{
				LOCK;
				--product;
				cvPdcr.notify_all();
				cout << "consume " << product << endl;
			}
		}

		{
			LOCK;
			cout << "consume finish" << endl;
		}
	};
	for (size_t i = 0; i < consumer; ++i)
		csmrThd.emplace_back(consume);
}

void Manager::join()
{
	for (thread& t : pdcrThd)
		t.join();
	for (thread& t : csmrThd)
		t.join();
}

int main()
{
	Manager m(8, 8, 8);
	m.join();

	return 0;
}
