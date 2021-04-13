#include "global.h"
#include "hTool.h"
#include "hTest.h"

#include "hRange.h"

using namespace std;
TEST_INIT() {}

enum RangeType
{
	RangeType_None,
	RangeType_Close,
	RangeType_Open,
	RangeType_CloseOpen,
	RangeType_OpenClose,
};

struct RangeItem
{
	uint8_t _ty = 0;
	int _min = 0;
	int _max = 0;
	RangeItem(uint8_t ty, int min, int max)
	{
		_ty = ty;
		_min = min;
		_max = max;
	}
	bool check(int val) const
	{
		switch (_ty)
		{
		case RangeType_Close: return val >= _min && val <= _max;
		case RangeType_Open: return val > _min && val < _max;
		case RangeType_CloseOpen: return val >= _min && val < _max;
		case RangeType_OpenClose: return val > _min && val <= _max;
		default:
			break;
		}

		return false;
	}
};

struct Range
{
	std::vector<RangeItem> items;
	bool check(int val) const
	{
		for (auto& item : items)
		{
			if (item.check(val))
				return true;
		}

		return false;
	}
};

Range range1;
hRange range2;

TEST(结果输出)
{
	range1.items.push_back(RangeItem(RangeType_CloseOpen, -0x7FFFFFFF, -10));
	range1.items.push_back(RangeItem(RangeType_Open, -8, -6));
	range1.items.push_back(RangeItem(RangeType_OpenClose, -6, -2));
	range1.items.push_back(RangeItem(RangeType_CloseOpen, 4, 8));
	range1.items.push_back(RangeItem(RangeType_Close, 11, 11));
	range1.items.push_back(RangeItem(RangeType_Close, 21, 31));
	range1.items.push_back(RangeItem(RangeType_Close, 41, 51));
	range1.items.push_back(RangeItem(RangeType_Close, 61, 71));
	range1.items.push_back(RangeItem(RangeType_Close, 81, 91));
	range1.items.push_back(RangeItem(RangeType_Close, 101, 111));
	range1.items.push_back(RangeItem(RangeType_Close, 121, 131));
	range1.items.push_back(RangeItem(RangeType_Close, 141, 151));
	range1.items.push_back(RangeItem(RangeType_Close, 161, 171));
	range1.items.push_back(RangeItem(RangeType_Close, 181, 191));
	range1.items.push_back(RangeItem(RangeType_Close, 201, 211));
	range1.items.push_back(RangeItem(RangeType_Close, 221, 231));
	range1.items.push_back(RangeItem(RangeType_Close, 241, 251));
	range1.items.push_back(RangeItem(RangeType_Close, 261, 271));
	range1.items.push_back(RangeItem(RangeType_Close, 281, 291));
	range1.items.push_back(RangeItem(RangeType_Close, 301, 311));
	range1.items.push_back(RangeItem(RangeType_Close, 321, 331));
	range1.items.push_back(RangeItem(RangeType_Close, 341, 351));
	range1.items.push_back(RangeItem(RangeType_Close, 361, 371));
	range1.items.push_back(RangeItem(RangeType_Close, 381, 391));
	range1.items.push_back(RangeItem(RangeType_Close, 401, 411));
	range1.items.push_back(RangeItem(RangeType_Close, 421, 431));
	range1.items.push_back(RangeItem(RangeType_Close, 441, 451));
	range1.items.push_back(RangeItem(RangeType_Close, 461, 471));
	range1.items.push_back(RangeItem(RangeType_Close, 481, 491));
	range1.items.push_back(RangeItem(RangeType_Close, 501, 511));
	range1.items.push_back(RangeItem(RangeType_Close, 521, 531));
	range1.items.push_back(RangeItem(RangeType_Close, 541, 551));
	range1.items.push_back(RangeItem(RangeType_Close, 561, 571));
	range1.items.push_back(RangeItem(RangeType_Close, 581, 591));
	range1.items.push_back(RangeItem(RangeType_Close, 601, 611));
	range1.items.push_back(RangeItem(RangeType_Close, 621, 631));
	range1.items.push_back(RangeItem(RangeType_Close, 641, 651));
	range1.items.push_back(RangeItem(RangeType_Close, 661, 671));
	range1.items.push_back(RangeItem(RangeType_Close, 681, 691));
	range1.items.push_back(RangeItem(RangeType_Close, 701, 711));
	range1.items.push_back(RangeItem(RangeType_Close, 721, 731));
	range1.items.push_back(RangeItem(RangeType_Close, 741, 751));
	range1.items.push_back(RangeItem(RangeType_Close, 761, 771));
	range1.items.push_back(RangeItem(RangeType_Close, 781, 791));
	range1.items.push_back(RangeItem(RangeType_Close, 801, 811));
	range1.items.push_back(RangeItem(RangeType_Close, 821, 831));
	range1.items.push_back(RangeItem(RangeType_Close, 841, 851));
	range1.items.push_back(RangeItem(RangeType_Close, 861, 871));
	range1.items.push_back(RangeItem(RangeType_Close, 881, 891));
	range1.items.push_back(RangeItem(RangeType_Close, 901, 911));
	range1.items.push_back(RangeItem(RangeType_Close, 921, 931));
	range1.items.push_back(RangeItem(RangeType_Close, 941, 951));
	range1.items.push_back(RangeItem(RangeType_Close, 961, 971));
	range1.items.push_back(RangeItem(RangeType_Close, 981, 991));
	range1.items.push_back(RangeItem(RangeType_Close, 1001, 1011));
	range1.items.push_back(RangeItem(RangeType_Close, 1021, 1031));
	range1.items.push_back(RangeItem(RangeType_Close, 1041, 1051));
	range1.items.push_back(RangeItem(RangeType_Close, 1061, 1071));
	range1.items.push_back(RangeItem(RangeType_Close, 1081, 1091));
	range1.items.push_back(RangeItem(RangeType_Close, 1101, 1111));
	range1.items.push_back(RangeItem(RangeType_Close, 1121, 1131));
	range1.items.push_back(RangeItem(RangeType_Close, 1141, 1151));
	range1.items.push_back(RangeItem(RangeType_Close, 1161, 1171));
	range1.items.push_back(RangeItem(RangeType_Close, 1181, 1191));
	range1.items.push_back(RangeItem(RangeType_Close, 1201, 1211));
	range1.items.push_back(RangeItem(RangeType_Close, 1221, 1231));
	range1.items.push_back(RangeItem(RangeType_Close, 1241, 1251));
	range1.items.push_back(RangeItem(RangeType_Close, 1261, 1271));
	range1.items.push_back(RangeItem(RangeType_Close, 1281, 1291));
	range1.items.push_back(RangeItem(RangeType_Close, 1301, 1311));
	range1.items.push_back(RangeItem(RangeType_Close, 1321, 1331));
	range1.items.push_back(RangeItem(RangeType_Close, 1341, 1351));
	range1.items.push_back(RangeItem(RangeType_Close, 1361, 1371));
	range1.items.push_back(RangeItem(RangeType_Close, 1381, 1391));
	range1.items.push_back(RangeItem(RangeType_Close, 1401, 1411));
	range1.items.push_back(RangeItem(RangeType_Close, 1421, 1431));
	range1.items.push_back(RangeItem(RangeType_Close, 1441, 1451));
	range1.items.push_back(RangeItem(RangeType_Close, 1461, 1471));
	range1.items.push_back(RangeItem(RangeType_Close, 1481, 1491));
	range1.items.push_back(RangeItem(RangeType_Close, 1501, 1511));
	range1.items.push_back(RangeItem(RangeType_Close, 1521, 1531));
	range1.items.push_back(RangeItem(RangeType_Close, 1541, 1551));
	range1.items.push_back(RangeItem(RangeType_Close, 1561, 1571));
	range1.items.push_back(RangeItem(RangeType_Close, 1581, 1591));
	range1.items.push_back(RangeItem(RangeType_Close, 1601, 1611));
	range1.items.push_back(RangeItem(RangeType_Close, 1621, 1631));
	range1.items.push_back(RangeItem(RangeType_Close, 1641, 1651));
	range1.items.push_back(RangeItem(RangeType_Close, 1661, 1671));
	range1.items.push_back(RangeItem(RangeType_Close, 1681, 1691));
	range1.items.push_back(RangeItem(RangeType_Close, 1701, 1711));
	range1.items.push_back(RangeItem(RangeType_Close, 1721, 1731));
	range1.items.push_back(RangeItem(RangeType_Close, 1741, 1751));
	range1.items.push_back(RangeItem(RangeType_Close, 1761, 1771));
	range1.items.push_back(RangeItem(RangeType_Close, 1781, 1791));
	range1.items.push_back(RangeItem(RangeType_Close, 1801, 1811));
	range1.items.push_back(RangeItem(RangeType_Close, 1821, 1831));
	range1.items.push_back(RangeItem(RangeType_Close, 1841, 1851));
	range1.items.push_back(RangeItem(RangeType_Close, 1861, 1871));
	range1.items.push_back(RangeItem(RangeType_Close, 1881, 1891));
	range1.items.push_back(RangeItem(RangeType_Close, 1901, 1911));
	range1.items.push_back(RangeItem(RangeType_Close, 1921, 1931));
	range1.items.push_back(RangeItem(RangeType_Close, 1941, 1951));
	range1.items.push_back(RangeItem(RangeType_Close, 1961, 1971));
	range1.items.push_back(RangeItem(RangeType_Close, 1981, 1991));
	range1.items.push_back(RangeItem(RangeType_Close, 2001, 2011));
	range1.items.push_back(RangeItem(RangeType_Close, 2021, 2031));
	range1.items.push_back(RangeItem(RangeType_Close, 2041, 2051));
	range1.items.push_back(RangeItem(RangeType_Close, 2061, 2071));
	range1.items.push_back(RangeItem(RangeType_Close, 2081, 2091));
	range1.items.push_back(RangeItem(RangeType_Close, 2101, 2111));
	range1.items.push_back(RangeItem(RangeType_Close, 2121, 2131));
	range1.items.push_back(RangeItem(RangeType_Close, 2141, 2151));
	range1.items.push_back(RangeItem(RangeType_Close, 2161, 2171));
	range1.items.push_back(RangeItem(RangeType_Close, 2181, 2191));
	range1.items.push_back(RangeItem(RangeType_Close, 2201, 2211));
	range1.items.push_back(RangeItem(RangeType_Close, 2221, 2231));
	range1.items.push_back(RangeItem(RangeType_Close, 2241, 2251));
	range1.items.push_back(RangeItem(RangeType_Close, 2261, 2271));
	range1.items.push_back(RangeItem(RangeType_Close, 2281, 2291));
	range1.items.push_back(RangeItem(RangeType_Close, 2301, 2311));
	range1.items.push_back(RangeItem(RangeType_Close, 2321, 2331));
	range1.items.push_back(RangeItem(RangeType_Close, 2341, 2351));
	range1.items.push_back(RangeItem(RangeType_Close, 2361, 2371));
	range1.items.push_back(RangeItem(RangeType_Close, 2381, 2391));
	range1.items.push_back(RangeItem(RangeType_Close, 2401, 2411));
	range1.items.push_back(RangeItem(RangeType_Close, 2421, 2431));
	range1.items.push_back(RangeItem(RangeType_Close, 2441, 2451));
	range1.items.push_back(RangeItem(RangeType_Close, 2461, 2471));
	range1.items.push_back(RangeItem(RangeType_Close, 2481, 2491));
	range1.items.push_back(RangeItem(RangeType_Close, 2501, 2511));
	range1.items.push_back(RangeItem(RangeType_Close, 2521, 2531));
	range1.items.push_back(RangeItem(RangeType_Close, 2541, 2551));
	range1.items.push_back(RangeItem(RangeType_Close, 2561, 2571));
	range1.items.push_back(RangeItem(RangeType_Close, 2581, 2591));
	range1.items.push_back(RangeItem(RangeType_Close, 2601, 2611));
	range1.items.push_back(RangeItem(RangeType_Close, 2621, 2631));
	range1.items.push_back(RangeItem(RangeType_Close, 2641, 2651));
	range1.items.push_back(RangeItem(RangeType_Close, 2661, 2671));
	range1.items.push_back(RangeItem(RangeType_Close, 2681, 2691));
	range1.items.push_back(RangeItem(RangeType_Close, 2701, 2711));
	range1.items.push_back(RangeItem(RangeType_Close, 2721, 2731));
	range1.items.push_back(RangeItem(RangeType_Close, 2741, 2751));
	range1.items.push_back(RangeItem(RangeType_Close, 2761, 2771));
	range1.items.push_back(RangeItem(RangeType_Close, 2781, 2791));
	range1.items.push_back(RangeItem(RangeType_Close, 2801, 2811));
	range1.items.push_back(RangeItem(RangeType_Close, 2821, 2831));
	range1.items.push_back(RangeItem(RangeType_Close, 2841, 2851));
	range1.items.push_back(RangeItem(RangeType_Close, 2861, 2871));
	range1.items.push_back(RangeItem(RangeType_Close, 2881, 2891));
	range1.items.push_back(RangeItem(RangeType_Close, 2901, 2911));
	range1.items.push_back(RangeItem(RangeType_Close, 2921, 2931));
	range1.items.push_back(RangeItem(RangeType_Close, 2941, 2951));
	range1.items.push_back(RangeItem(RangeType_Close, 2961, 2971));
	range1.items.push_back(RangeItem(RangeType_Close, 2981, 2991));

	range2.insert(VernierType_Less, -10);
	range2.insert(VernierType_Greater, -8);
	range2.insert(VernierType_Unequal, -6);
	range2.insert(VernierType_LessEqual, -2);
	range2.insert(VernierType_GreaterEqual, 4);
	range2.insert(VernierType_Less, 8);
	range2.insert(VernierType_Equal, 11);
	range2.insert(VernierType_LessEqual,	21);
	range2.insert(VernierType_GreaterEqual, 31);
	range2.insert(VernierType_LessEqual,	41);
	range2.insert(VernierType_GreaterEqual, 51);
	range2.insert(VernierType_LessEqual,	61);
	range2.insert(VernierType_GreaterEqual, 71);
	range2.insert(VernierType_LessEqual,	81);
	range2.insert(VernierType_GreaterEqual, 91);
	range2.insert(VernierType_LessEqual,	101);
	range2.insert(VernierType_GreaterEqual, 111);
	range2.insert(VernierType_LessEqual,	121);
	range2.insert(VernierType_GreaterEqual, 131);
	range2.insert(VernierType_LessEqual,	141);
	range2.insert(VernierType_GreaterEqual, 151);
	range2.insert(VernierType_LessEqual,	161);
	range2.insert(VernierType_GreaterEqual, 171);
	range2.insert(VernierType_LessEqual,	181);
	range2.insert(VernierType_GreaterEqual, 191);
	range2.insert(VernierType_LessEqual,	201);
	range2.insert(VernierType_GreaterEqual, 211);
	range2.insert(VernierType_LessEqual,	221);
	range2.insert(VernierType_GreaterEqual, 231);
	range2.insert(VernierType_LessEqual,	241);
	range2.insert(VernierType_GreaterEqual, 251);
	range2.insert(VernierType_LessEqual,	261);
	range2.insert(VernierType_GreaterEqual, 271);
	range2.insert(VernierType_LessEqual,	281);
	range2.insert(VernierType_GreaterEqual, 291);
	range2.insert(VernierType_LessEqual,	301);
	range2.insert(VernierType_GreaterEqual, 311);
	range2.insert(VernierType_LessEqual,	321);
	range2.insert(VernierType_GreaterEqual, 331);
	range2.insert(VernierType_LessEqual,	341);
	range2.insert(VernierType_GreaterEqual, 351);
	range2.insert(VernierType_LessEqual,	361);
	range2.insert(VernierType_GreaterEqual, 371);
	range2.insert(VernierType_LessEqual,	381);
	range2.insert(VernierType_GreaterEqual, 391);
	range2.insert(VernierType_LessEqual,	401);
	range2.insert(VernierType_GreaterEqual, 411);
	range2.insert(VernierType_LessEqual,	421);
	range2.insert(VernierType_GreaterEqual, 431);
	range2.insert(VernierType_LessEqual,	441);
	range2.insert(VernierType_GreaterEqual, 451);
	range2.insert(VernierType_LessEqual,	461);
	range2.insert(VernierType_GreaterEqual, 471);
	range2.insert(VernierType_LessEqual,	481);
	range2.insert(VernierType_GreaterEqual, 491);
	range2.insert(VernierType_LessEqual,	501);
	range2.insert(VernierType_GreaterEqual, 511);
	range2.insert(VernierType_LessEqual,	521);
	range2.insert(VernierType_GreaterEqual, 531);
	range2.insert(VernierType_LessEqual,	541);
	range2.insert(VernierType_GreaterEqual, 551);
	range2.insert(VernierType_LessEqual,	561);
	range2.insert(VernierType_GreaterEqual, 571);
	range2.insert(VernierType_LessEqual,	581);
	range2.insert(VernierType_GreaterEqual, 591);
	range2.insert(VernierType_LessEqual,	601);
	range2.insert(VernierType_GreaterEqual, 611);
	range2.insert(VernierType_LessEqual,	621);
	range2.insert(VernierType_GreaterEqual, 631);
	range2.insert(VernierType_LessEqual,	641);
	range2.insert(VernierType_GreaterEqual, 651);
	range2.insert(VernierType_LessEqual,	661);
	range2.insert(VernierType_GreaterEqual, 671);
	range2.insert(VernierType_LessEqual,	681);
	range2.insert(VernierType_GreaterEqual, 691);
	range2.insert(VernierType_LessEqual,	701);
	range2.insert(VernierType_GreaterEqual, 711);
	range2.insert(VernierType_LessEqual,	721);
	range2.insert(VernierType_GreaterEqual, 731);
	range2.insert(VernierType_LessEqual,	741);
	range2.insert(VernierType_GreaterEqual, 751);
	range2.insert(VernierType_LessEqual,	761);
	range2.insert(VernierType_GreaterEqual, 771);
	range2.insert(VernierType_LessEqual,	781);
	range2.insert(VernierType_GreaterEqual, 791);
	range2.insert(VernierType_LessEqual,	801);
	range2.insert(VernierType_GreaterEqual, 811);
	range2.insert(VernierType_LessEqual,	821);
	range2.insert(VernierType_GreaterEqual, 831);
	range2.insert(VernierType_LessEqual,	841);
	range2.insert(VernierType_GreaterEqual, 851);
	range2.insert(VernierType_LessEqual,	861);
	range2.insert(VernierType_GreaterEqual, 871);
	range2.insert(VernierType_LessEqual,	881);
	range2.insert(VernierType_GreaterEqual, 891);
	range2.insert(VernierType_LessEqual,	901);
	range2.insert(VernierType_GreaterEqual, 911);
	range2.insert(VernierType_LessEqual,	921);
	range2.insert(VernierType_GreaterEqual, 931);
	range2.insert(VernierType_LessEqual,	941);
	range2.insert(VernierType_GreaterEqual, 951);
	range2.insert(VernierType_LessEqual,	961);
	range2.insert(VernierType_GreaterEqual, 971);
	range2.insert(VernierType_LessEqual,	981);
	range2.insert(VernierType_GreaterEqual, 991);
	range2.insert(VernierType_LessEqual,	1001);
	range2.insert(VernierType_GreaterEqual, 1011);
	range2.insert(VernierType_LessEqual,	1021);
	range2.insert(VernierType_GreaterEqual, 1031);
	range2.insert(VernierType_LessEqual,	1041);
	range2.insert(VernierType_GreaterEqual, 1051);
	range2.insert(VernierType_LessEqual,	1061);
	range2.insert(VernierType_GreaterEqual, 1071);
	range2.insert(VernierType_LessEqual,	1081);
	range2.insert(VernierType_GreaterEqual, 1091);
	range2.insert(VernierType_LessEqual,	1101);
	range2.insert(VernierType_GreaterEqual, 1111);
	range2.insert(VernierType_LessEqual,	1121);
	range2.insert(VernierType_GreaterEqual, 1131);
	range2.insert(VernierType_LessEqual,	1141);
	range2.insert(VernierType_GreaterEqual, 1151);
	range2.insert(VernierType_LessEqual,	1161);
	range2.insert(VernierType_GreaterEqual, 1171);
	range2.insert(VernierType_LessEqual,	1181);
	range2.insert(VernierType_GreaterEqual, 1191);
	range2.insert(VernierType_LessEqual,	1201);
	range2.insert(VernierType_GreaterEqual, 1211);
	range2.insert(VernierType_LessEqual,	1221);
	range2.insert(VernierType_GreaterEqual, 1231);
	range2.insert(VernierType_LessEqual,	1241);
	range2.insert(VernierType_GreaterEqual, 1251);
	range2.insert(VernierType_LessEqual,	1261);
	range2.insert(VernierType_GreaterEqual, 1271);
	range2.insert(VernierType_LessEqual,	1281);
	range2.insert(VernierType_GreaterEqual, 1291);
	range2.insert(VernierType_LessEqual,	1301);
	range2.insert(VernierType_GreaterEqual, 1311);
	range2.insert(VernierType_LessEqual,	1321);
	range2.insert(VernierType_GreaterEqual, 1331);
	range2.insert(VernierType_LessEqual,	1341);
	range2.insert(VernierType_GreaterEqual, 1351);
	range2.insert(VernierType_LessEqual,	1361);
	range2.insert(VernierType_GreaterEqual, 1371);
	range2.insert(VernierType_LessEqual,	1381);
	range2.insert(VernierType_GreaterEqual, 1391);
	range2.insert(VernierType_LessEqual,	1401);
	range2.insert(VernierType_GreaterEqual, 1411);
	range2.insert(VernierType_LessEqual,	1421);
	range2.insert(VernierType_GreaterEqual, 1431);
	range2.insert(VernierType_LessEqual,	1441);
	range2.insert(VernierType_GreaterEqual, 1451);
	range2.insert(VernierType_LessEqual,	1461);
	range2.insert(VernierType_GreaterEqual, 1471);
	range2.insert(VernierType_LessEqual,	1481);
	range2.insert(VernierType_GreaterEqual, 1491);
	range2.insert(VernierType_LessEqual,	1501);
	range2.insert(VernierType_GreaterEqual, 1511);
	range2.insert(VernierType_LessEqual,	1521);
	range2.insert(VernierType_GreaterEqual, 1531);
	range2.insert(VernierType_LessEqual,	1541);
	range2.insert(VernierType_GreaterEqual, 1551);
	range2.insert(VernierType_LessEqual,	1561);
	range2.insert(VernierType_GreaterEqual, 1571);
	range2.insert(VernierType_LessEqual,	1581);
	range2.insert(VernierType_GreaterEqual, 1591);
	range2.insert(VernierType_LessEqual,	1601);
	range2.insert(VernierType_GreaterEqual, 1611);
	range2.insert(VernierType_LessEqual,	1621);
	range2.insert(VernierType_GreaterEqual, 1631);
	range2.insert(VernierType_LessEqual,	1641);
	range2.insert(VernierType_GreaterEqual, 1651);
	range2.insert(VernierType_LessEqual,	1661);
	range2.insert(VernierType_GreaterEqual, 1671);
	range2.insert(VernierType_LessEqual,	1681);
	range2.insert(VernierType_GreaterEqual, 1691);
	range2.insert(VernierType_LessEqual,	1701);
	range2.insert(VernierType_GreaterEqual, 1711);
	range2.insert(VernierType_LessEqual,	1721);
	range2.insert(VernierType_GreaterEqual, 1731);
	range2.insert(VernierType_LessEqual,	1741);
	range2.insert(VernierType_GreaterEqual, 1751);
	range2.insert(VernierType_LessEqual,	1761);
	range2.insert(VernierType_GreaterEqual, 1771);
	range2.insert(VernierType_LessEqual,	1781);
	range2.insert(VernierType_GreaterEqual, 1791);
	range2.insert(VernierType_LessEqual,	1801);
	range2.insert(VernierType_GreaterEqual, 1811);
	range2.insert(VernierType_LessEqual,	1821);
	range2.insert(VernierType_GreaterEqual, 1831);
	range2.insert(VernierType_LessEqual,	1841);
	range2.insert(VernierType_GreaterEqual, 1851);
	range2.insert(VernierType_LessEqual,	1861);
	range2.insert(VernierType_GreaterEqual, 1871);
	range2.insert(VernierType_LessEqual,	1881);
	range2.insert(VernierType_GreaterEqual, 1891);
	range2.insert(VernierType_LessEqual,	1901);
	range2.insert(VernierType_GreaterEqual, 1911);
	range2.insert(VernierType_LessEqual,	1921);
	range2.insert(VernierType_GreaterEqual, 1931);
	range2.insert(VernierType_LessEqual,	1941);
	range2.insert(VernierType_GreaterEqual, 1951);
	range2.insert(VernierType_LessEqual,	1961);
	range2.insert(VernierType_GreaterEqual, 1971);
	range2.insert(VernierType_LessEqual,	1981);
	range2.insert(VernierType_GreaterEqual, 1991);
	range2.insert(VernierType_LessEqual,	2001);
	range2.insert(VernierType_GreaterEqual, 2011);
	range2.insert(VernierType_LessEqual,	2021);
	range2.insert(VernierType_GreaterEqual, 2031);
	range2.insert(VernierType_LessEqual,	2041);
	range2.insert(VernierType_GreaterEqual, 2051);
	range2.insert(VernierType_LessEqual,	2061);
	range2.insert(VernierType_GreaterEqual, 2071);
	range2.insert(VernierType_LessEqual,	2081);
	range2.insert(VernierType_GreaterEqual, 2091);
	range2.insert(VernierType_LessEqual,	2101);
	range2.insert(VernierType_GreaterEqual, 2111);
	range2.insert(VernierType_LessEqual,	2121);
	range2.insert(VernierType_GreaterEqual, 2131);
	range2.insert(VernierType_LessEqual,	2141);
	range2.insert(VernierType_GreaterEqual, 2151);
	range2.insert(VernierType_LessEqual,	2161);
	range2.insert(VernierType_GreaterEqual, 2171);
	range2.insert(VernierType_LessEqual,	2181);
	range2.insert(VernierType_GreaterEqual, 2191);
	range2.insert(VernierType_LessEqual,	2201);
	range2.insert(VernierType_GreaterEqual, 2211);
	range2.insert(VernierType_LessEqual,	2221);
	range2.insert(VernierType_GreaterEqual, 2231);
	range2.insert(VernierType_LessEqual,	2241);
	range2.insert(VernierType_GreaterEqual, 2251);
	range2.insert(VernierType_LessEqual,	2261);
	range2.insert(VernierType_GreaterEqual, 2271);
	range2.insert(VernierType_LessEqual,	2281);
	range2.insert(VernierType_GreaterEqual, 2291);
	range2.insert(VernierType_LessEqual,	2301);
	range2.insert(VernierType_GreaterEqual, 2311);
	range2.insert(VernierType_LessEqual,	2321);
	range2.insert(VernierType_GreaterEqual, 2331);
	range2.insert(VernierType_LessEqual,	2341);
	range2.insert(VernierType_GreaterEqual, 2351);
	range2.insert(VernierType_LessEqual,	2361);
	range2.insert(VernierType_GreaterEqual, 2371);
	range2.insert(VernierType_LessEqual,	2381);
	range2.insert(VernierType_GreaterEqual, 2391);
	range2.insert(VernierType_LessEqual,	2401);
	range2.insert(VernierType_GreaterEqual, 2411);
	range2.insert(VernierType_LessEqual,	2421);
	range2.insert(VernierType_GreaterEqual, 2431);
	range2.insert(VernierType_LessEqual,	2441);
	range2.insert(VernierType_GreaterEqual, 2451);
	range2.insert(VernierType_LessEqual,	2461);
	range2.insert(VernierType_GreaterEqual, 2471);
	range2.insert(VernierType_LessEqual,	2481);
	range2.insert(VernierType_GreaterEqual, 2491);
	range2.insert(VernierType_LessEqual,	2501);
	range2.insert(VernierType_GreaterEqual, 2511);
	range2.insert(VernierType_LessEqual,	2521);
	range2.insert(VernierType_GreaterEqual, 2531);
	range2.insert(VernierType_LessEqual,	2541);
	range2.insert(VernierType_GreaterEqual, 2551);
	range2.insert(VernierType_LessEqual,	2561);
	range2.insert(VernierType_GreaterEqual, 2571);
	range2.insert(VernierType_LessEqual,	2581);
	range2.insert(VernierType_GreaterEqual, 2591);
	range2.insert(VernierType_LessEqual,	2601);
	range2.insert(VernierType_GreaterEqual, 2611);
	range2.insert(VernierType_LessEqual,	2621);
	range2.insert(VernierType_GreaterEqual, 2631);
	range2.insert(VernierType_LessEqual,	2641);
	range2.insert(VernierType_GreaterEqual, 2651);
	range2.insert(VernierType_LessEqual,	2661);
	range2.insert(VernierType_GreaterEqual, 2671);
	range2.insert(VernierType_LessEqual,	2681);
	range2.insert(VernierType_GreaterEqual, 2691);
	range2.insert(VernierType_LessEqual,	2701);
	range2.insert(VernierType_GreaterEqual, 2711);
	range2.insert(VernierType_LessEqual,	2721);
	range2.insert(VernierType_GreaterEqual, 2731);
	range2.insert(VernierType_LessEqual,	2741);
	range2.insert(VernierType_GreaterEqual, 2751);
	range2.insert(VernierType_LessEqual,	2761);
	range2.insert(VernierType_GreaterEqual, 2771);
	range2.insert(VernierType_LessEqual,	2781);
	range2.insert(VernierType_GreaterEqual, 2791);
	range2.insert(VernierType_LessEqual,	2801);
	range2.insert(VernierType_GreaterEqual, 2811);
	range2.insert(VernierType_LessEqual,	2821);
	range2.insert(VernierType_GreaterEqual, 2831);
	range2.insert(VernierType_LessEqual,	2841);
	range2.insert(VernierType_GreaterEqual, 2851);
	range2.insert(VernierType_LessEqual,	2861);
	range2.insert(VernierType_GreaterEqual, 2871);
	range2.insert(VernierType_LessEqual,	2881);
	range2.insert(VernierType_GreaterEqual, 2891);
	range2.insert(VernierType_LessEqual,	2901);
	range2.insert(VernierType_GreaterEqual, 2911);
	range2.insert(VernierType_LessEqual,	2921);
	range2.insert(VernierType_GreaterEqual, 2931);
	range2.insert(VernierType_LessEqual,	2941);
	range2.insert(VernierType_GreaterEqual, 2951);
	range2.insert(VernierType_LessEqual,	2961);
	range2.insert(VernierType_GreaterEqual, 2971);
	range2.insert(VernierType_LessEqual,	2981);
	range2.insert(VernierType_GreaterEqual, 2991);

	int n = 1;
	cout << "range1" << endl;
	for (int i = -12; i < 15; ++i, ++n)
	{
		cout << i << "(" << range1.check(i) << ")\t";

		if (!(n % 6))
			cout << endl;
	}
	cout << endl;
	n = 1;
	cout << "range2" << endl;
	for (int i = -12; i < 15; ++i, ++n)
	{
		cout << i << "(" << range2.check(i) << ")\t";

		if (!(n % 6))
			cout << endl;
	}
	cout << endl;
}

#define CNT 100

TEST(普通范围比较)
{
	for (size_t n = 0; n < CNT; ++n)
	{
		for (int i = -12; i < 3000; ++i)
			range1.check(i);
	}
}

TEST(红黑树范围比较)
{
	for (size_t n = 0; n < CNT; ++n)
	{
		for (int i = -12; i < 3000; ++i)
			range2.check(i);
	}
}

TEST_MAIN()