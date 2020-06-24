#include <iostream>
#include <vector>

#include <thread>
#include <mutex>
#include <chrono>

#include "Philosopher.h"

using namespace std;

mutex coutM;
#define COUT_LK(x) { lock_guard<mutex> lk(coutM); cout << x << endl; }

PhilosopherMgr::PhilosopherMgr(const size_t& cnt) : cnt(cnt)
{
	vecRunCv.reserve(cnt);
	vecP.reserve(cnt);

	vecRunCv.push_back(new condition_variable);
	for (size_t i = 0; i < cnt; ++i)
	{
		if (i + 1 < cnt)
			vecRunCv.push_back(new condition_variable);
		vecP.push_back(new Philosopher(*this, i, mtx, *vecRunCv[i], begCv));
	}
}

PhilosopherMgr::~PhilosopherMgr()
{
	for (auto& pMLk : vecRunCv)
		delete pMLk;
	for (auto& pP : vecP)
		delete pP;
}

const bool& PhilosopherMgr::getNotify(const size_t& id) const
{
	if (id >= cnt)
		return false;
	return vecP[id]->isNotify();
}

void PhilosopherMgr::setNotify(const size_t& id, const bool& isNotify)
{
	if (id >= cnt)
		return;
	vecP[id]->setNotify(isNotify);
}

void PhilosopherMgr::notifyNext(const size_t& id)
{
	if (id >= cnt)
		return;
	vecP[(id + 1) % cnt]->notify();
}

void PhilosopherMgr::run()
{
	for (size_t i = 0; i < cnt; ++i)
		vecT.emplace_back(*vecP[i]);
	lock_guard<mutex> lk(mtx);
	begId = 0;
	begCv.notify_all();
	vecP.front()->setNotify(true);
}

void PhilosopherMgr::join()
{
	for (auto& t : vecT)
		t.join();
}

void Philosopher::notify()
{
	setNotify(true);
	runCv.notify_one();
}

void Philosopher::operator()()
{
	mutex m;
	unique_lock<mutex> lk(m);

	for (size_t i = 0; i < 2; ++i)
	{
		//COUT_LK(id << "beg wait");
		begCv.wait(lk, [&]
			{
				if (mgr.isBeg())
					return true;
				return mgr.checkBegId(id);
			});
		//COUT_LK(id << "beg");
		if (!mgr.isBeg())
		{
			lock_guard<mutex> lk(mtx);
			mgr.setBeg(true);
			begCv.notify_all();
		}
		//COUT_LK(id << "run wait");
		runCv.wait(lk, [&]
			{
				bool notifyTmp = mgr.getNotify(id);
				if (notifyTmp)
					mgr.setNotify(id, false);
				return notifyTmp;
			});
		//COUT_LK(id << "mutex");
		unique_lock<mutex> lk(mtx);
		//COUT_LK(id << "run");
		COUT_LK(id << "do someting");
		lk.unlock();
		//COUT_LK(id << "notify next");
		mgr.notifyNext(id);
	}
}

#undef COUT_LK