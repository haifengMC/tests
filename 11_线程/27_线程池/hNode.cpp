#include "global.h"
#include "hThread.h"

namespace hThread
{
	void hNode::init(size_t id, PhNodeData data)
	{
		_id = id;
		_data = data;
	}
}