#include <iostream>
#include <map>

using namespace std;

class A
{
public:
	A(int) {}
	A(const A&) = delete;
};

ostream& operator<<(ostream& os, const A& a) { return os << "A"; }

int main()
{
	map<int, A> m;
	map<int, int> intM;
	A a(1);
	//m[1] = a; //ok
	//m.insert({ 1, a });
	//m.insert(p);

	//m.insert(p);
	
	
	return 0;
}