#include <set>
#include <map>
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
	case VernierType_Equal: return val == _val;
	case VernierType_Unequal: return val != _val;
	case VernierType_Greater: return val > _val;
	case VernierType_Less: return val < _val;
	case VernierType_GreaterEqual: return val >= _val;
	case VernierType_LessEqual: return val <= _val;
	default:
		break;
	}

    return false;
}

void hRange::insert(uint8_t tp, int val)
{
	if (!tp || tp >= VernierType_Max)
		return;

	_vern.insert(std::make_pair(val, hVernier(tp, val)));
}

bool hRange::check(int val) const
{
	if (_vern.empty())
		return false;

    auto itRight = _vern.lower_bound(val);
    if (itRight != _vern.end())
        return itRight->second.check(val);

	auto itLeft = std::prev(itRight);
	if (itLeft == _vern.end())
		return false;

	return itLeft->second.check(val);
}
