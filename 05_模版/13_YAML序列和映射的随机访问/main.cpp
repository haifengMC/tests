#include "global.h"
#include "hConfig.h"

using namespace std;

int main()
{
	YAML::NodeEx node;
	"test.yml" >> node;
	YAML::NodeEx n0 = node["lucy"][(long long)atoi("0")];
	cout << n0 << endl;
	cout << node << endl;
	"test2.yml" << node;

	return 0;
}