#include "global.h"
#include "hThread.h"

namespace hThread
{
	std::ostream& NodeData::debugShow(std::ostream& os, uint8_t n, char c)
	{
		os << std::string(n++, c) << "[NodeData]" <<
			" id:" << id << 
			" needDel:" << needDel << 
			" totalElapsed:" << totalElapsed;

		return os;
	}

	void TaskNode::init(size_t id, hTool::hAutoPtr<NodeData> data)
	{
		_id = id;
		_data = data;
	}

	std::ostream& TaskNode::debugShow(std::ostream& os, uint8_t n, char c)
	{
		os << std::string(n++, c) << "[TaskNode]" <<
			" id:" << _id;

		return os;
	}
}