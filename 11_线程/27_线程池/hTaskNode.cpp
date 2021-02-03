#include "global.h"
#include "hThread.h"

namespace hThread
{
	void TaskNode::init(size_t id, PNodeData data)
	{
		_id = id;
		_data = data;
	}
}