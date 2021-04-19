#include <string>
#include <list>
#include <set>
#include <map>
#include <functional>
#include <unordered_set>
#include <unordered_map>
#include <iostream>

using namespace std;

set<string> variables = { "WA", "NT", "Q", "NSW", "V", "SA", "T" };
set<string> domain = { "red", "green", "blue" };
unordered_map<string, unordered_set<string>> constraints = 
{
	{"WA", {"NT", "SA"}},
	{"NT", {"WA", "SA", "Q"}},
	{"Q", {"NT", "SA", "NSW"}},
	{"NSW", {"Q", "V", "SA"}},
	{"V", {"NSW", "SA"}},
	{"SA", {"WA", "NT", "Q", "NSW", "V"}}
};
list<map<string, string>> resultList;

bool check(const string& v, const string& d, map<string, string>& result)
{
	if (result.empty())
		return true;

	auto itSet = constraints.find(v);
	if (itSet == constraints.end())
		return true;

	for (auto& vC : itSet->second)
	{
		auto itRes = result.find(vC);
		if (itRes == result.end())
			continue;

		if (d == itRes->second)
			return false;
	}

	return true;
}

void solute(map<string, string> result = map<string, string>(),pair<string, string> lastV = make_pair("", ""), set<string>::const_iterator curVIt = variables.begin())
{
	if (variables.empty())
		return;

	for (auto& d : domain)
	{
		if (!check(*curVIt, d, result))
			continue;

		result[*curVIt] = d;
		if (++curVIt == variables.end())
		{
			resultList.push_back(result);
			return;
		}
		
		solute(result, std::make_pair(*curVIt, d), curVIt);
	}

}

void print()
{
	cout << "生成" << resultList.size() << "个结果" << endl;
	for (auto& result : resultList)
	{
		for (auto& var : result)
			cout << var.first << ":" << var.second << " ";

		cout << endl;
	}
}

int main()
{
	solute();
	print();

	return 0;
}