#include "global.h"
#include "UserFunc.h"
#include "UserFunc1.h"
#include "UserEvent.h"

using namespace std;

template <>
static UserFuncBase* UserFuncBase::factory<UserFuncType_1>() { return new UserFunc1(); }
UserFunc1::RegUserFunc1 reg;
UserFunc1::RegUserFunc1::RegUserFunc1()
{
	UserFuncBase::factMap[UserFuncType_1] = 
		UserFuncBase::factory < UserFuncType_1>;
}

void UserFunc1::printMe()
{
	cout << "UserFunc1:" << sizeof(reg) << endl;
}

void UserFunc1::initEvent()
{
	cout << "UserFunc1::doRegAct1连接事件动作->事件" << UserEventType_Reg << endl;
	conn(UserEventType_Reg, function<void()>(bind(mem_fn(&UserFunc1::doRegAct1), this)));
	cout << "UserFunc1::doRegAct2连接事件动作->事件" << UserEventType_Reg << endl;
	conn(UserEventType_Reg, function<void()>(bind(mem_fn(&UserFunc1::doRegAct2), this)), 3);
	cout << "UserFunc1::doEvt1Act连接事件动作->事件" << UserEventType_Func1Evt1 << endl;
	conn(UserEventType_Func1Evt1, function<void()>(bind(mem_fn(&UserFunc1::doEvt1Act), this)));
	cout << "UserFunc1::doEvt1Act连接事件动作->事件" << UserEventType_Func1Evt2 << endl;
	conn(UserEventType_Func1Evt2, function<void()>(bind(mem_fn(&UserFunc1::doEvt2Act), this)));
}

void UserFunc1::doRegAct1()
{
	cout << "UserFunc1::doRegAct1执行动作" << endl;
}

void UserFunc1::doRegAct2()
{
	cout << "UserFunc1::doRegAct2执行动作" << endl;
	emit(UserEventType_Func1Evt1);
}

void UserFunc1::doEvt1Act()
{
	cout << "UserFunc1::doEvt1Act执行动作" << endl;
}

void UserFunc1::doEvt2Act()
{
	cout << "UserFunc1::doEvt2Act执行动作" << endl;
	emit(UserEventType_Func2Evt1);
}
