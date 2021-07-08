#pragma once

class UserFuncBase;
struct UserFunc1 : public UserFuncBase
{
	void printMe();
	void initEvent();

	struct RegUserFunc1 { RegUserFunc1(); };
private:
	void doRegAct1();
	void doRegAct2();
	void doEvt1Act();
	void doEvt2Act();
};