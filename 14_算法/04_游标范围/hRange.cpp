#include <set>
#include "hRange.h"

hVernier::hVernier(int val)
{
	_val = val;
}

bool hRange::check(int val) const
{
    auto itRight = _vern.lower_bound(val);

	switch (VernierType)
	{
    case VernierType_Equal:
        break;
    case VernierType_Unequal:
        break;
    case VernierType_Greater:
        break;
    case VernierType_Less:
        break;
    case VernierType_GreaterEqual:
        break;
    case VernierType_LessEqual:
        break;
    default:
        break;
	}

	return false;
}
