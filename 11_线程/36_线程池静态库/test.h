#pragma once

struct Test2TaskData : public hThread::NodeData
{
	std::string _s;
	void update(size_t opt, ...);
};

struct Test2TaskNode : public hThread::TaskNode
{
	std::string _s;

	bool preProc();
	bool onProc();
	bool finalProc();
};

class Test2Task : public hThread::Task
{
public:
	Test2Task();
	bool canRepeat();
};