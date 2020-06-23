#include <iostream>
#include <vector>

#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

mutex coutM;
#define COUT_LK(x) { lock_guard<mutex> lk(coutM); cout << x << endl; }

class Manager;
class Philosopher
{
	Manager& mgr;
	size_t id = 0;
	mutex *left, *right, *last, *self;
	condition_variable* cv, *thCv;

	bool isRecord = false;
public:
	Philosopher(Manager& mgr, const size_t& id, mutex* left, mutex* right, mutex* last, mutex* self, condition_variable* cv, condition_variable* thCv) :
		mgr(mgr), id(id), left(left), right(right), last(last), self(self), cv(cv), thCv(thCv) {}
	
	void setLast(mutex* last) { this->last = last; }

	void lock() { last->lock(); }
	void unlock() { last->unlock(); }

	void operator()();
};

class Manager
{
	size_t cnt = 0, thCnt = 0;
	vector<mutex*> vecM;
	vector <mutex*> vecCV;
	vector<Philosopher*> vecP;
	vector<thread> vecT;
	condition_variable runCV, thdCV;

	bool m_isRun = false;
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
			vecP.push_back(new Philosopher(*this, i, vecM[(i) % cnt], vecM[(i + 1) % cnt], last, vecCV[i], &runCV, &thdCV));
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
			vecT.emplace_back(*vecP[i]);

		this_thread::sleep_for(chrono::seconds(1));

		waitRun();

		vecM.front()->unlock();
		//vecP.back()->unlock();
	}
	void recordRunThread() { ++thCnt; }
	void waitRun()
	{
		mutex m;
		unique_lock<mutex> lk(m);
		thdCV.wait(lk, [&] 
			{
				return thCnt + 1 >= cnt;
			});

		m_isRun = true;
		runCV.notify_all();
	}
	const bool& isRun() const { return m_isRun; }

	void join()
	{
		for (auto& t : vecT)
			t.join();
	}
};

void Philosopher::operator()()
{
	mutex m;
	unique_lock<mutex> lk(m);

	for (size_t i = 0; i < 2; ++i)
	{
		//COUT_LK(id << " wait lock");
		last->lock();
		//COUT_LK(id << " lock");
		right->lock();
		//COUT_LK(id << " lock right");

		cv->wait(lk, [&] 
			{ 
				if (!isRecord)
				{
					isRecord = true;
					mgr.recordRunThread();
					thCv->notify_one();
				}
				return mgr.isRun(); 
			});

		left->lock();
		//COUT_LK(id << " lock left");
		last->unlock();
		//COUT_LK(id << " unlock last");
		COUT_LK(id << " do someting");
		this_thread::yield();
		//this_thread::sleep_for(chrono::microseconds(100));
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

int main()
{
	Manager m(100);

	m.run();
	m.join();

	return 0;
}