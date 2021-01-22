#include <unordered_map>
#include <iostream>

using namespace std;

struct MapId
{
	int _x = 0;
	int _y = 0;

	MapId(int x, int y)
	{
		_x = x;
		_y = y;
	}
	bool operator== (const MapId& id) const { return _x == id._x && _y == id._y; }
};

struct MapIdHash { size_t operator()(const MapId& id) const { return hash<uint64_t>()(id._x << 32 | id._y); } };

int main()
{
	
	unordered_map<int, int> m = { {1, 2}, {2, 3}, {3, 4} };
	bool first = true;
	for (auto& pr : m)
	{
		if (first) first = false;
		else cout << ",";
		
		cout << "{" << pr.first << " " << pr.second << "}";
	}
	cout << endl;

	unordered_multimap < MapId, char, MapIdHash> mm;
	typedef decltype(mm)::iterator MapIt;
	typedef pair<MapIt, MapIt> MapRange;
	mm.insert(make_pair(MapId(1, 2), 'a'));
	mm.insert(make_pair(MapId(1, 2), 'b'));
	mm.insert(make_pair(MapId(2, 2), 'b'));
	mm.insert(make_pair(MapId(2, 2), 'c'));
	mm.insert(make_pair(MapId(2, 2), 'b'));
	mm.insert(make_pair(MapId(3, 2), 'd'));

	auto printMm = [](MapIt beg, MapIt end)
	{
		bool first = true;
		for (; beg != end; ++beg)
		{
			if (first) first = false;
			else cout << ",";

			cout << "{[" << beg->first._x << "," << beg->first._y << "]" << beg->second << "}";
		}
		cout << endl;
	};

	printMm(mm.begin(), mm.end());
	MapRange range = mm.equal_range(MapId(2, 2));
	printMm(range.first, range.second);
	range = mm.equal_range(MapId(2, 2));

	return 0;
}