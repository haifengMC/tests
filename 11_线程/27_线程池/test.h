#pragma once

//��д������
void readFunc(int i);
void writeFunc(int i);

//����������Զ������ݺͽڵ�
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

//id������debug
#define InsertTask(va)\
	Task* va = new Task(50, 2, TaskAttrType::Loop);\
	va->initNodeData(new TestNodeData("test data"));\
	va->addNode(new TestTaskNode("test node1"));\
	va->addNode(new TestTaskNode("test node2"));\
	cout << _tasksIdGen.insert(va).second << endl

//����ָ�����3
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
//����ָ�����4
struct Test4B;
struct Test4A : public hTool::hAutoPtrObj
{
	const char* name = "A";
	hTool::hAutoPtr<Test4B> _pB;
	void addPtr(hTool::hAutoPtr<Test4B> pB);

	~Test4A() { std::cout << "~TestA()" << std::endl; }

	void fillAddList(std::list<hTool::hAutoPtrBase*>&);
	void fillDecList(std::list<hTool::hAutoPtrBase*>&);
	//void destoryPtr(const void* pT);
};
struct Test4B : public hTool::hAutoPtrObj
{
	const char* name = "B";
	hTool::hAutoPtr<Test4A> _pA;
	void addPtr(hTool::hAutoPtr<Test4A> pA);

	~Test4B() { std::cout << "~TestB()" << std::endl; }

	void fillAddList(std::list<hTool::hAutoPtrBase*>&);
	void fillDecList(std::list<hTool::hAutoPtrBase*>&);
	//void destoryPtr(const void* pT);
};
#define Test4P(n)\
	cout << n << endl;\
	hTool::hAutoPtr<Test4A>::debugMap(cout);\
	hTool::hAutoPtr<Test4B>::debugMap(cout);\
	cout << string(10, '-') << endl
