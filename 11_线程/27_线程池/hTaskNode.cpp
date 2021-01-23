#include "global.h"
#include "hThread.h"

namespace hThread
{
	void TaskNode::init(size_t id, hTool::hAutoPtr<NodeData> data)
	{
		_id = id;
		_data = data;
	}
}