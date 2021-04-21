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
					PhTask pTask = _pTaskMgr->getTask(id);
					if (!pTask)
						return false;

					return pTask->checkStat(TaskStatType::Wait);
				}, taskId)),
			std::function<void()>(std::bind(
				[&](size_t id, std::function<void(PWhUserDt)> memFn)
				{
					PhTask pTask = _pTaskMgr->getTask(id);
					if (!pTask)
						return;

					PWhUserDt pData = pTask->getUserData();
					if (!pData)
						return;

					pData->writeLk([&]() { memFn(pData); });
					pushTask2Weight(pTask);
				}, taskId,
				std::function<void(PWhUserDt)>(bind(
					std::mem_fn(&hUserData::update),
					std::placeholders::_1, opt, args...)))));
	}
}
