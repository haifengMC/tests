#include <iostream>
#include <vector>

#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

mutex coutM;
#define COUT_LK(x) { lock_guard<mutex> lk(coutM); cout << x << endl; }

class Philosopher
{
	size_t id = 0;
	mutex *left, *right, *last, *self;
public:
	Philosopher(const size_t& id, mutex* left, mutex* right, mutex* last, mutex* self) :
		id(id), left(left), right(right), last(last), self(self) {}
	
	void setLast(mutex* last) { this->last = last; }

	void lock() { last->lock(); }
	void unlock() { last->unlock(); }

	void operator()()
	{
		for (size_t i = 0; i < 2; ++i)
		{
			//COUT_LK(id << " wait lock");
			last->lock();
			//COUT_LK(id << " lock");
			right->lock();
			//COUT_LK(id << " lock right");
			left->lock();
			//COUT_LK(id << " lock left");
			last->unlock();
			//COUT_LK(id << " unlock last");
			COUT_LK(id << " do someting");
			//this_thread::yield();
			//this_thread::sleep_for(chrono::seconds(1));
			right->unlock();
			//COUT_LK(id << " unlock left");
			left->unlock();
			//COUT_LK(id << " unlock right");
			self->lock();
			//COUT_LK(id << " unlock self");
			self->unlock();
		}
	}
};

class Manager
{
	size_t cnt = 0;
	vector<mutex*> vecM;
	vector <mutex*> vecCV;
	vector<Philosopher*> vecP;
	vector<thread> vecT;
public:
	Manager(const size_t& cnt) : cnt(cnt) 
	{
		vecM.reserve(cnt);
		vecCV.reserve(cnt);
		vecP.reserve(cnt);

		vecM.push_back(new mutex);
		vecCV.push_back(new mutex);
		for (size_t i = 0; i < cnt; ++i)
		{
			if (i + 1 < cnt)
			{
				vecM.push_back(new mutex);
				vecCV.push_back(new mutex);
			}
			mutex* last = i ? vecCV[i - 1] : NULL;
			vecP.push_back(new Philosopher(i, vecM[(i) % cnt], vecM[(i + 1) % cnt], last, vecCV[i]));
		}
		vecP.front()->setLast(vecCV.back());
	}

	~Manager()
	{
		for (auto& pM : vecM)
			delete pM;
		for (auto& pMLk : vecCV)
			delete pMLk;
		for (auto& pP : vecP)
			delete pP;
	}

	void run()
	{
		//vecP.back()->lock();
		vecM.front()->lock();
		
		for (size_t i = 0; i < cnt; ++i)
		{
			vecT.emplace_back(*vecP[i]);
			this_thread::sleep_for(chrono::microseconds(100));
		}

		vecM.front()->unlock();
		//vecP.back()->unlock();
	}

	void join()
	{
		for (auto& t : vecT)
			t.join();
	}
};

int main()
{
	Manager m(100);

	m.run();
	m.join();

	return 0;
}