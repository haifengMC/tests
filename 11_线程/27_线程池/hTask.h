#pragma once


namespace hThread
{
	class Task
	{
		friend class ThreadMem;

		size_t id = 0;
		size_t weight = 0;//权重
		size_t thrdExpect = 0;//期待线程数

		bool running = false;
		bool loop = false;
		std::set<size_t> thrdId;
		std::list<TaskNode*> nodeList;
		std::list<TaskNode*>::iterator nodeIt = nodeList.end();
	public:
		const size_t& getId() const { return id; }
		const size_t& getWeight() const { return weight; }
		const size_t& getThrdNum() const { return thrdExpect; }

		TaskNode* getNextNode();

		void insertThrd(const size_t& id) { thrdId.insert(id); }
		//返回实际使用的线程数
		size_t runTask(const size_t& rate);
	};
}