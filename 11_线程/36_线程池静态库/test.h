#pragma once

struct Test2TaskData : public hThread::hUserData
{
	std::string _s;
	void update(size_t opt, ...);
};

struct Test2TaskNode : public hThread::hNode
{
	std::string _s;

	bool preProc();
	bool onProc();
	bool finalProc();
};

class Test2Task : public hThread::hTask
{
public:
	Test2Task();
	bool canRepeat();
};