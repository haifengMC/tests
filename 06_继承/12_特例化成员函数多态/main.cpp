#include <iostream>

using namespace std;

enum UserEvent
{
	UserEvent_Reg,
	UserEvent_Login,
};

class UserBase
{
public:
	template <size_t N>
	void onEvent() {}
	template <>
	virtual void onEvent<UserEvent_Reg>() {}
	template <>
	virtual void onEvent<UserEvent_Login>() {}
};

class User1 : public UserBase
{
public:
	template <size_t N>
	void onEvent() {}
	template <>
	virtual void onEvent<UserEvent_Reg>() { cout << "User1 Reg" << endl; }
	template <>
	virtual void onEvent<UserEvent_Login>() { cout << "User1 Login" << endl; }
};

class User2 : public UserBase
{
public:
	template <size_t N>
	void onEvent() {}
	template <>
	virtual void onEvent<UserEvent_Reg>() { cout << "User2 Reg" << endl; }
	template <>
	virtual void onEvent<UserEvent_Login>() { cout << "User2 Login" << endl; }
};

int main()
{
	UserBase* pUser1 = new User1;
	UserBase* pUser2 = new User2;

	pUser1->onEvent<UserEvent_Reg>();
	pUser2->onEvent<UserEvent_Login>();

	return 0;
}