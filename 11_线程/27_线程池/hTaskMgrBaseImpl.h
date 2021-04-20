#pragma once

namespace hThread
{
	template <size_t N>
	size_t hTaskMgrBase::commitTasks(PhTask(&task)[N])
	{
		if (!N) return 0;
		return commitTasks(task, N);
	}

	template <typename ... Args >
	void hTaskMgrBase::updateTaskData(size_t taskId, size_t opt, Args ... args)
	{
		addUpdateTaskFunc(
			taskId,
			std::function<bool()>(std::bind(
				[&](size_t id)
				{
					PhTask pTask = _tasks.get(id);
					if (!pTask)
						return false;

					return pTask->checkStat(TaskStatType::Wait);
				}, taskId)),
			std::function<void()>(std::bind(
				[&](size_t id, std::function<void(hUserData*)> memFn)
				{
					PhTask pTask = _tasks.get(id);
					if (!pTask)
						return;

					pTask->writeLk([&]()
						{
							PhTskStcDt pAttr = pTask->getStc();
							if (!pAttr)
								return;

							memFn(pAttr->_nodeData.operator ->());
						});
					_weights.pushBack(pTask->getWeight(), id);
				}, taskId,
				std::function<void(hUserData*)>(bind(
					std::mem_fn(&hUserData::update),
					std::placeholders::_1, opt, args...)))));
	}
}
