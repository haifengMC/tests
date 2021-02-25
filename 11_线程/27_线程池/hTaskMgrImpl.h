#pragma once

namespace hThread
{
	template <size_t N>
	size_t TaskMgr::commitTasks(PTask(&task)[N])
	{
		if (!N) return 0;
		return commitTasks(task, N);
	}

	template <typename ... Args >
	void TaskMgr::updateTaskData(size_t taskId, size_t opt, Args ... args)
	{
		addUpdateTaskFunc(
			taskId,
			std::function<bool()>(std::bind(
				[&](size_t id)
				{
					PTask pTask = _tasks.get(id);
					if (!pTask)
						return false;

					bool ret = true;
					pTask->readLk([&]() { ret = pTask->checkStat(TaskStatType::Wait); });
					return ret;
				}, taskId)),
			std::function<void()>(std::bind(
				[&](size_t id, std::function<void(NodeData*)> memFn)
				{
					PTask pTask = _tasks.get(id);
					if (!pTask)
						return;

					pTask->writeLk([&]()
						{
							PTaskAttr pAttr = pTask->getAttr();
							if (!pAttr)
								return;

							memFn(pAttr->_nodeData.operator ->());
						});
					_weights.pushBack(pTask->getWeight(), id);
				}, taskId,
				std::function<void(NodeData*)>(bind(
					std::mem_fn(&NodeData::update),
					std::placeholders::_1, opt, args...)))));
	}
}
