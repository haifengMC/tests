#pragma once

//读写锁测试
void readFunc(int i);
void writeFunc(int i);

//向任务添加自定义数据和节点
struct TestNodeData : public hThread::NodeData
{
	std::string testInfo;
	
	TestNodeData(const char* info);
};

struct TestTaskNode : public hThread::TaskNode
{
	std::string testInfo;

	TestTaskNode(const char* info);
};

//id生成器debug
#define InsertTask(va)\
	Task* va = new Task(50, 2, TaskAttrType::Loop);\
	va->initNodeData(new TestNodeData("test data"));\
	va->addNode(new TestTaskNode("test node1"));\
	va->addNode(new TestTaskNode("test node2"));\
	cout << _tasksIdGen.insert(va).second << endl

//智能指针测试
struct TestC;
struct TestA 
{
	hTool::hAutoPtr<TestC> _pC;
	void addPtr(hTool::hAutoPtr<TestC> pC);

	~TestA() { std::cout << "~TestA()" << std::endl; }
};
struct TestB 
{
	hTool::hAutoPtr<TestA> _pA;
	void addPtr(hTool::hAutoPtr<TestA> pA);

	~TestB() { std::cout << "~TestB()" << std::endl; }
};
struct TestC
{
	hTool::hAutoPtr<TestB> _pB;
	void addPtr(hTool::hAutoPtr<TestB> pB);

	~TestC() { std::cout << "~TestC()" << std::endl; }
};
#define TestP(n)\
	cout << n << endl;\
	hTool::hAutoPtr<TestA>::debugMap(cout);\
	hTool::hAutoPtr<TestB>::debugMap(cout);\
	hTool::hAutoPtr<TestC>::debugMap(cout);\
	cout << string(10, '-') << endl
