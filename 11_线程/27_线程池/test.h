#pragma once

//读写锁测试
void readFunc(int i);
void writeFunc(int i);

//向任务添加自定义数据和节点
struct TestNodeData : public hThread::hUserData
{
	std::string testInfo;
	
	TestNodeData(const char* info);
};

struct TestTaskNode : public hThread::hNode
{
	std::string testInfo;

	TestTaskNode(const char* info);
};

//id生成器debug
#define InsertTask(va)\
	hTask* va = new hTask(50, 2, TaskAttrType::Loop);\
	va->initNodeData(new TestNodeData("test data"));\
	va->addNode(new TestTaskNode("test node1"));\
	va->addNode(new TestTaskNode("test node2"));\
	cout << _tasksIdGen.insert(va).second << endl

//智能指针测试3
struct Test3C;
struct Test3A 
{
	hTool::hAutoPtr<Test3C> _pC;
	void addPtr(hTool::hAutoPtr<Test3C> pC);

	~Test3A() { std::cout << "~TestA()" << std::endl; }
};
struct Test3B 
{
	hTool::hAutoPtr<Test3A> _pA;
	void addPtr(hTool::hAutoPtr<Test3A> pA);

	~Test3B() { std::cout << "~TestB()" << std::endl; }
};
struct Test3C
{
	hTool::hAutoPtr<Test3B> _pB;
	void addPtr(hTool::hAutoPtr<Test3B> pB);

	~Test3C() { std::cout << "~TestC()" << std::endl; }
};
#define Test3P(n)\
	cout << n << endl;\
	hTool::hAutoPtr<Test3A>::debugMap(cout);\
	hTool::hAutoPtr<Test3B>::debugMap(cout);\
	hTool::hAutoPtr<Test3C>::debugMap(cout);\
	cout << string(10, '-') << endl
//智能指针测试4
struct Test4B;
struct Test4A
{
	const char* name = "A";
	hTool::hWeakPtr<Test4B> _pB;
	void addPtr(hTool::hWeakPtr<Test4B> pB);

	~Test4A() { std::cout << "~TestA()" << std::endl; }
};
struct Test4B
{
	const char* name = "B";
	hTool::hWeakPtr<Test4A> _pA;
	void addPtr(hTool::hWeakPtr<Test4A> pA);

	~Test4B() { std::cout << "~TestB()" << std::endl; }
};
#define Test4P(n)\
	cout << n << endl;\
	hTool::hAutoPtr<Test4A>::debugMap(cout);\
	hTool::hAutoPtr<Test4B>::debugMap(cout);\
	cout << string(10, '-') << endl


//智能指针测试5
struct Test5Base
{
	virtual ~Test5Base() {}
};

struct Test5 : public Test5Base
{
	~Test5() {}
};

//线程池运行5秒
struct Test1TaskNode : public hThread::hNode
{
	bool onProc();
};

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