#pragma once

namespace hThread
{
	struct UpdateTaskData : public NodeData
	{
		std::list<std::function<void()>> _updateList;
	};

	struct UpdateTaskNode : public TaskNode
	{
		std::list<std::function<void()>> _execList;

		bool preProc();
		bool onProc();
		bool finalProc();
	};

	class UpdateTask : public Task
	{
	public:
		UpdateTask();
		void updata(std::function<void()>& fn);
	};
}
