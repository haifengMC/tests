#include <iostream>
#include <map>
#include <unordered_map>

#include "User.h"

using namespace std;

int main()
{
	User u;
	u.loadFunc();
	u.initEvents();
	u.printEveryFunc();

	return 0;
}