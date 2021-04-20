#include "global.h"
#include "hThread.h"
#include "hNode.h"

namespace hThread
{
	void hNode::init(size_t id, PhUserData data)
	{
		_id = id;
		_data = data;
	}

	bool hNode::handle_initProc()
	{
		return initProc();
	}

	bool hNode::handle_preProc()
	{
		bool ret = true;
		_data->readLk([&]() { ret = preProc(); });
		return ret;
	}

	bool hNode::handle_onProc()
	{
		bool ret = true;
		_data->writeLk([&]() { ret = onProc(); });
		return ret;
	}

	bool hNode::handle_finalProc()
	{
		return finalProc();
	}

}