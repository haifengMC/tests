#pragma once

struct Test2TaskData : public hThread::hUserData
{
	std::list<std::string> _sLst;
	void update(size_t opt, void* data, size_t len) override;
};

struct Test2TaskNode : public hThread::hNode
{
	std::string _s;

	bool preProc();
	bool onProc();
	bool finalProc();
};

class Test2Task : public hThread::hTaskBase
{
public:
	Test2Task();
	bool canRepeat() const override;
};