#include <iostream>
#include <set>
#include <map>
#include "hRange.h"

using namespace std;

int main()
{
	hRange range;
	range.insert(VernierType_Less, -10);
	range.insert(VernierType_Greater, -8);
	range.insert(VernierType_Unequal, -6);
	range.insert(VernierType_LessEqual, -2);
	range.insert(VernierType_GreaterEqual, 4);
	range.insert(VernierType_Less, 8);
	range.insert(VernierType_Equal, 11);

	int n = 1;
	for (int i = -12; i < 15; ++i, ++n)
	{
		cout << i << "(" << range.check(i) << ")\t";

		if (!(n % 6))
			cout << endl;
	}

	return 0;
}