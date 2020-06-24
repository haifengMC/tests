#pragma once

class Philosopher;
class PhilosopherMgr
{
	size_t cnt = 0, begId = -1;
	bool m_isBeg = false;
	std::mutex mtx;//自锁
	std::condition_variable begCv;//开启条件
	std::vector <std::condition_variable*> vecRunCv;//运行条件

	std::vector<Philosopher*> vecP;//
	std::vector<std::thread> vecT;//线程管理
public:

	PhilosopherMgr(const size_t& cnt);
	~PhilosopherMgr();

	const bool& getNotify(const size_t& id) const;
	void setNotify(const size_t& id, const bool& isNotify);
	void notifyNext(const size_t& id);

	bool isBeg() { return m_isBeg; }
	void setBeg(bool b) { m_isBeg = b; }
	bool checkBegId(const size_t& id) const { return id == begId; }

	void run();
	void join();
};

class Philosopher
{
	PhilosopherMgr& mgr;
	size_t id = 0;
	bool m_isNotify = false;

	std::mutex& mtx;
	std::condition_variable& runCv, & begCv;
public:

	Philosopher(PhilosopherMgr& mgr, const size_t& id, std::mutex& mtx,
		std::condition_variable& runCv, std::condition_variable& begCv) :
		mgr(mgr), id(id), mtx(mtx), runCv(runCv), begCv(begCv) {}

	const bool& isNotify() const { return m_isNotify; }
	void setNotify(const bool& n) { m_isNotify = n; }
	void notify();
	void operator()();
};