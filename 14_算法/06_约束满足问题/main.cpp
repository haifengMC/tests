#include <string>
#include <list>
#include <set>
#include <map>
#include <chrono>
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
list<unordered_map<string, string>> resultList;

bool check(const string& v, const string& d, unordered_map<string, string>& result)
{
	if (result.empty())
		return true;

	auto itSet = constraints.find(v);
	if (itSet == end(constraints))
		return true;

	for (auto& vC : itSet->second)
	{
		auto itRes = result.find(vC);
		if (itRes == end(result))
			continue;

		if (d == itRes->second)
			return false;
	}

	return true;
}

void solute(
	unordered_map<string, string> result = unordered_map<string, string>(), 
	set<string>::const_iterator curVIt = begin(variables))
{
	if (variables.empty())
		return;

	for (auto& d : domain)
	{
		auto tempRes = result;
		if (!check(*curVIt, d, tempRes))
			continue;

		tempRes[*curVIt] = d;
		if (next(curVIt) == end(variables))
			resultList.push_back(tempRes);
		else
			solute(tempRes, next(curVIt));
	}
}

void print(size_t elapsed)
{
	cout << "生成" << resultList.size() << "个结果,用时" << elapsed << "ms" << endl;
	for (auto& result : resultList)
	{
		for (auto& var : result)
			cout << var.first << ":" << var.second << "  ";

		cout << endl;
	}
}

int main()
{
	auto start = chrono::high_resolution_clock::now();	
	solute();
	print(chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count());

	return 0;
}