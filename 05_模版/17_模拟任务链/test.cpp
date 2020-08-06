#include "global.h"
#include "hSingleton.h"
#include "hTest.h"
#include "hTool.h"
#include "test.h"

using namespace std;

#define NEW_SAFE(X) [&]() { cout << "new " << #X << endl; return new X; }()
#define DEL_SAFE(X)  { cout << "delete " << #X << endl; delete X; }

struct NodeData
{
	size_t id = 0;
	bool needDel = false;
	uint64_t totalElapsed = 0;
	map<size_t, uint64_t> elapsedRecord;//id-time

	NodeData() {}
	NodeData(const size_t& id) : id(id) {}
	virtual ~NodeData() {}

	operator bool() { return needDel; }
};

class Task;
class Node
{
	friend class Task;
protected:
	NodeData* data = NULL;
public:
	virtual NodeData* getNextData() { return data; }

	virtual bool preProcess() { return true; }//预处理
	virtual bool onProcess() { return true; }//处理函数
	virtual bool afterProcess() { return true; }//
};

class Task
{
	list<Node*> nodeList;
public:
	Task() {}
	Task(initializer_list<Node*> il) : nodeList(il) {}
	~Task()
	{
		for (Node*& n : nodeList)
			DEL_SAFE(n);
	}


	template<typename F>
	NodeData* exeEvery(F func, NodeData* const& data = NULL)
	{
		size_t idx = 0;
		NodeData* dataTemp = data;

		uint64_t totalElapsed = 0;
		map<size_t, uint64_t> elapsedRecord;

		for (Node*& n : nodeList)
		{
			if (!dataTemp)
				n->data = NEW_SAFE(NodeData(idx));
			else
			{
				n->data = dataTemp;
				n->data->id = idx;
			}
			n->data->totalElapsed = totalElapsed;
			n->data->elapsedRecord = elapsedRecord;

			auto start = std::chrono::high_resolution_clock::now();
			bool ret = func(n, dataTemp);
			auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
			if (elapsedRecord.insert(std::make_pair(idx, elapsed)).second)
				totalElapsed += elapsed;
			if (!ret) break;

			if (dataTemp != n->getNextData() && dataTemp != data)
				DEL_SAFE(dataTemp);

			dataTemp = n->getNextData();
			++idx;
		}

		if (dataTemp)
		{
			dataTemp->id = idx;
			dataTemp->elapsedRecord = elapsedRecord;
			dataTemp->totalElapsed = totalElapsed;
			if (dataTemp != data)
				dataTemp->needDel = true;
		}

		return dataTemp;
	}
};

NodeData* runTask(Task* const& pTask, NodeData* const& data = NULL)
{
	return pTask->exeEvery([](Node*& n, NodeData* const& data)
		{
			if (n->preProcess())
				n->onProcess();

			if (n->afterProcess())
				return true;
			else
				return false;
		}, data);
}

TEST_INIT(Tst, testAll)

#define DATA dynamic_cast<Tst1_Data*>(data)

struct Tst1_Data : public NodeData
{
	int a;
	int b;

	Tst1_Data(const int& a, const int& b) : a(a), b(b) {}
};

struct Tst1_Node1 : public Node
{
	virtual bool preProcess()
	{
		if (!DATA)
			return false;

		return true;
	}

	virtual bool onProcess() 
	{
		cout << DATA->a + DATA->b << endl;

		return true; 
	}//处理函数
};

struct Tst1_Node2 : public Node
{
	virtual bool preProcess()
	{
		if (!DATA)
			return false;

		return true;
	}

	virtual bool onProcess()
	{
		cout << DATA->a * DATA->b << endl;

		return true;
	}//处理函数
};

TEST(Tst, Tst1)
{
	Tst1_Data dataTmp(1, 2);

	Task task = { NEW_SAFE(Tst1_Node1), NEW_SAFE(Tst1_Node2) };
	NodeData* data = runTask(&task, &dataTmp);
	Tst1_Data* tst1Data = DATA;
	cout << tst1Data << " " << (&dataTmp == tst1Data) << endl;
}
#undef DATA

////////////////////////////////////////////////////////////
struct Tst2_Data1 : public NodeData
{
	int a;
	int b;

	Tst2_Data1(const int& a, const int& b) : a(a), b(b) {}
};
struct Tst2_Data2 : public NodeData
{
	int sum;

	Tst2_Data2(const int& sum) : sum(sum) {}
};

struct Tst2_Node1 : public Node
{
#define DATA1 dynamic_cast<Tst2_Data1*>(data)
	virtual bool preProcess()
	{
		if (!DATA1)
			return false;

		return true;
	}

	virtual bool onProcess()
	{
		cout << "[" << data->id << "]"  << data->totalElapsed << "(usec) " << DATA1->a << " " << DATA1->b << endl;
		data = NEW_SAFE(Tst2_Data2(DATA1->a + DATA1->b));
		
		return true;
	}//处理函数
#undef DATA1
};

struct Tst2_Data3 : public NodeData
{
	int pow;

	Tst2_Data3(const int& pow) : pow(pow) {}
};

struct Tst2_Node2 : public Node
{
#define DATA2 dynamic_cast<Tst2_Data2*>(data)
	virtual bool preProcess()
	{
		if (!DATA2)
			return false;

		return true;
	}

	virtual bool onProcess()
	{
		cout << "[" << data->id << "]" << data->totalElapsed << "(usec) " << DATA2->sum << endl;
		data = NEW_SAFE(Tst2_Data3(DATA2->sum * DATA2->sum));

		return true;
	}//处理函数
#undef DATA2
};

TEST(Tst, Tst2)
{
	Tst2_Data1 dataTmp(1, 2);

	Task task = { NEW_SAFE(Tst2_Node1), NEW_SAFE(Tst2_Node2) };
	NodeData* data = runTask(&task, &dataTmp);
	Tst2_Data3* pData = dynamic_cast<Tst2_Data3*>(data);
	cout << pData << " " << (data == &dataTmp) << endl;

	ostringstream os;
	os << "[" << pData->id << "]" << pData->totalElapsed << "(usec) " << pData->pow << "\n";
	if (*pData)
		for (auto& p : pData->elapsedRecord)
		{
			os << "[" << p.first << "]" << p.second << "\n";
		}
	cout << os.str().c_str();

	DEL_SAFE(pData);
}
//////////////////////////////////////////////////////////////
struct Tst3_Node : public Node
{
	virtual bool onProcess()
	{
		hTool::Container c(cout);
		cout << "[" << data->id << "]" << data->totalElapsed << "(usec)" << endl;
		c(data->elapsedRecord) << endl;
		return true;
	}//处理函数
};

TEST(Tst, Tst3)
{
	Task task = { NEW_SAFE(Tst3_Node), NEW_SAFE(Tst3_Node), NEW_SAFE(Tst3_Node) };
	NodeData* data = runTask(&task);

	hTool::Container c(cout);
	cout << "[" << data->id << "]" << data->totalElapsed << "(usec)" << endl;
	c(data->elapsedRecord) << endl;

	if (*data)
		DEL_SAFE(data);
}
//////////////////////////////////////////////////////////////
struct Tst4_Node : public Node
{
	virtual bool onProcess()
	{
		hTool::Container c(cout);
		cout << "[" << data->id << "]" << data->totalElapsed << "(usec)" << endl;
		c(data->elapsedRecord) << endl;
		return true;
	}//处理函数
};

TEST(Tst, Tst4)
{
	NodeData dataTmp;
	Task task = { NEW_SAFE(Tst4_Node), NEW_SAFE(Tst4_Node), NEW_SAFE(Tst4_Node) };
	NodeData* data = runTask(&task, &dataTmp);

	hTool::Container c(cout);
	cout << "[" << data->id << "]" << data->totalElapsed << "(usec)" << endl;
	c(data->elapsedRecord) << endl;

	if (*data)
		DEL_SAFE(data);
}

