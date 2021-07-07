#include <iostream>
#include <unordered_map>

#include "UserFunc.h"
#include "UserFunc1.h"

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