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
		typedef std::unordered_map<size_t, ItemData> UpdateMap;
	}
	struct hUpdateData : public hUserData
	{
		UpdateTaskDefine::UpdateMap _updateMap;

		void updateTask(size_t taskId,
			std::function<bool()>& checkFn,
			std::function<void()>& execFn);
	};

	struct UpdateTaskNode : public hNode
	{
		UpdateTaskDefine::ExecFnList _execList;

		bool preProc();
		bool onProc();
		bool finalProc();
	};

	class hUpdateTask : public hTaskBase
	{
	public:
		hUpdateTask();
		void update(size_t taskId,
			std::function<bool()>& checkFn,
			std::function<void()>& execFn);
		bool canRepeat() const override;
	};
}
