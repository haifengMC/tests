#include <iostream>
#include <unordered_map>

#include "UserFunc.h"
#include "UserFunc2.h"

using namespace std;

template <>
static UserFuncBase* UserFuncBase::factory<UserFuncType_2>() { return new UserFunc2; }
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