#pragma once

namespace hThread
{
	namespace UpdateTaskDefine
	{
		typedef std::function<bool()> CheckFn;
		typedef std::function<void()> ExecFn;
		typedef std::list<ExecFn> ExecFnList;

		struct ItemData
		{
			size_t _taskId = 0;
			CheckFn _checkFn;
			ExecFnList _execList;

			ItemData(size_t taskId,
				std::function<bool()>& checkFn,
				std::function<void()>& execFn)
			{
				_taskId = taskId;
				_checkFn = checkFn;
				_execList.push_back(execFn);
			}
		};
		typedef std::map<size_t, ItemData> UpdateMap;
	}
	struct UpdateTaskData : public NodeData
	{
		UpdateTaskDefine::UpdateMap _updateMap;
	};

	struct UpdateTaskNode : public TaskNode
	{
		UpdateTaskDefine::ExecFnList _execList;

		bool preProc();
		bool onProc();
		bool finalProc();
	};

	class UpdateTask : public Task
	{
	public:
		UpdateTask();
		void updata(size_t taskId,
			std::function<bool()>& checkFn,
			std::function<void()>& execFn);
		bool canRepeat();
	};
}
