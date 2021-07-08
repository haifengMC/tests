#include "global.h"
#include "User.h"
#include "UserEvent.h"

using namespace std;

int main()
{
	User u;
	u.loadFunc();
	u.initEvents();
	u.printEveryFunc();

	u.emit(UserEventType_Reg);
	while (u.checkCurEvtList())
		u.doCurEvtList();

	return 0;
}