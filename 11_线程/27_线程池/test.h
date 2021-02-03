#pragma once

//读写锁测试
void readFunc(int i);
void writeFunc(int i);

//向任务添加自定义数据和节点
struct TestNodeData : public hThread::NodeData
{
	std::string testInfo;
	
	TestNodeData(const char* info);
	std::ostream& debugShow(std::ostream& os, uint8_t n = 0, char c = '\t');
};

struct TestTaskNode : public hThread::TaskNode
{
	std::string testInfo;

	TestTaskNode(const char* info);
	std::ostream& debugShow(std::ostream& os, uint8_t n = 0, char c = '\t');
};

//id生成器debug
#define InsertTask(va)\
	Task* va = new Task(50, 2, TaskAttrType::Loop);\
	va->initNodeData(new TestNodeData("test data"));\
	va->addNode(new TestTaskNode("test node1"));\
	va->addNode(new TestTaskNode("test node2"));\
	cout << _tasksIdGen.insert(va).second << endl

//智能指针测试
struct TestB;
struct TestA
{
	hTool::hAutoPtr<TestB> _pB;
	void addThis(hTool::hAutoPtr<TestB> pB);
	void destoryPtr();
	~TestA() { std::cout << "~TestA()" << std::endl; }
};
struct TestB
{
	hTool::hAutoPtr<TestA> _pA;
	void destoryPtr();
	~TestB() { std::cout << "~TestB()" << std::endl; }
};