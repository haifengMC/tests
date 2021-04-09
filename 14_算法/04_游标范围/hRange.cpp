#include <set>
#include "hRange.h"

hVernier::hVernier(int val)
{
	_val = val;
}

hVernier::hVernier(uint8_t ty, int val)
{
	_ty = ty;
	_val = val;
}

bool hVernier::check(int val) const
{
	switch (_ty)
	{
	case VernierType_Equal: return _val == val;
	case VernierType_Unequal: return _val != val;
	case VernierType_Greater: return _val > val;
	case VernierType_Less: return _val < val;
	case VernierType_GreaterEqual: return _val >= val;
	case VernierType_LessEqual: return _val <= val;
	default:
		break;
	}

    return false;
}

void hRange::inserVern(uint8_t tp, int val)
{
	if (!tp || tp >= VernierType_Max)
		return;

	auto it = _vern.find(val);
	bool ret = check(val);

	switch (tp)
	{
	case VernierType_Equal: 
	{
		if (ret)
			return;

		if (it == _vern.end())
			_vern.insert()
	}
	break;
	case VernierType_Unequal: 
	{
		if (!ret)
			return;

	}
	break;
	default:
		break;
	}
	
}

bool hRange::check(int val) const
{
	if (_vern.empty())
		return false;

    auto itRight = _vern.lower_bound(val);
    if (itRight != _vern.end())
        return itRight->check(val);

	auto itLeft = std::prev(itRight);
	if (itLeft == _vern.end())
		return false;

	return itLeft->check(val);
}
