#include <iostream>

using namespace std;

template <size_t N>
struct EventBase {};

enum UserEvent
{
	UserEvent_Reg,
	UserEvent_Login,
};

class UserBase
{
public:
	virtual void onEvent(const EventBase<UserEvent_Reg>&) {}
	virtual void onEvent(const EventBase<UserEvent_Login>&) {}
};

class User1 : public UserBase
{
public:
	void onEvent(const EventBase<UserEvent_Reg>&) { cout << "User1 Reg" << endl; }
	void onEvent(const EventBase<UserEvent_Login>&) { cout << "User1 Login" << endl; }
};

class User2 : public UserBase
{
public:
	void onEvent(const EventBase<UserEvent_Reg>&) { cout << "User2 Reg" << endl; }
	void onEvent(const EventBase<UserEvent_Login>&) { cout << "User2 Login" << endl; }
};

int main()
{
	UserBase* userArr[] = { new User1, new User2 };

	userArr[0]->onEvent(EventBase<UserEvent_Reg>());
	userArr[1]->onEvent(EventBase<UserEvent_Login>());

	return 0;
}