#include "global.h"
#include "UserFunc.h"
#include "UserFunc2.h"
#include "UserEvent.h"

using namespace std;

template <>
static UserFuncBase* UserFuncBase::factory<UserFuncType_2>() { return new UserFunc2(); }
UserFunc2::RegUserFunc2 reg;
UserFunc2::RegUserFunc2::RegUserFunc2()
{
	UserFuncBase::factMap[UserFuncType_2] =
		UserFuncBase::factory < UserFuncType_2>;
}

void UserFunc2::printMe()
{
	cout << "UserFunc2:" << sizeof(reg) << endl;
}

void UserFunc2::initEvent()
{
	cout << "UserFunc2::doRegAct1�����¼�����->�¼�" << UserEventType_Reg << endl;
	conn(UserEventType_Reg, function<void()>(bind(mem_fn(&UserFunc2::doRegAct1), this)));
	cout << "UserFunc2::doRegAct2�����¼�����->�¼�" << UserEventType_Reg << endl;
	conn(UserEventType_Reg, function<void()>(bind(mem_fn(&UserFunc2::doRegAct2), this)), 1);
	cout << "UserFunc2::doEvt1Act�����¼�����->�¼�" << UserEventType_Func2Evt1 << endl;
	conn(UserEventType_Func2Evt1, function<void()>(bind(mem_fn(&UserFunc2::doEvt1Act), this)));
}

void UserFunc2::doRegAct1()
{
	cout << "UserFunc2::doRegAct1ִ�ж���" << endl;
}

void UserFunc2::doRegAct2()
{
	cout << "UserFunc2::doRegAct2ִ�ж���" << endl;
	emit(UserEventType_Func1Evt2);
}

void UserFunc2::doEvt1Act()
{
	cout << "UserFunc2::doEvt1Actִ�ж���" << endl;
}
