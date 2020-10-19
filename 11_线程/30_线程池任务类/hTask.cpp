#include "global.h"
#include "hTool.h"
#include "hTask.h"

Task::Task(hTool::hAutoPtr<TaskAttr> attr) :
	hTool::hUniqueMapVal<size_t, Task>(thisId, this) 
{
	this->attr = attr;
}

Task::Task(Task&& t) :
	hTool::hUniqueMapVal<size_t, Task>(thisId, this)
{
	attr = std::move(t.attr);
	stat = std::move(t.stat);
}