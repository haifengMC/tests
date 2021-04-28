#include "global.h"
#include "hThread.h"
#include "hThread/hPoolMgr.h"
#include "test.h"

using namespace std;
using namespace hThread;

int main()
{
	shPool.run();
	{
		string is;
		PhTask t;
		t.bind(new Test2Task);
		shPool.commitTasks(t);
		while (1)
		{
			cin >> is;
			if (is == "quit")
				break;
			else if (is == "print")
			{
				ostringstream os;
				Debug(os, shPool);
				COUT_LK(os.str());
				continue;
			}

			cout << "提交更新:" << is.c_str() << " " << is.size() << endl;
			t->updateTaskData(100, is.c_str(), is.size() + 1);
		}
	}

	ostringstream os;
	Debug(os, shPool);
	COUT_LK(os.str());

	shPool.stop();
	Debug_PtrMap(cout);
	hTool::hAutoPtr<hTool::hWeakPtrBase>::debugMap(cout);
	shPoolFin;
	Debug_PtrMap(cout);
	hTool::hAutoPtr<hTool::hWeakPtrBase>::debugMap(cout);

	return 0;
}