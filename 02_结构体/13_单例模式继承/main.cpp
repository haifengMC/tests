#include "global.h"
#include "hSingleton.h"
#include "hTool.h"

using namespace std;
hTool::Container ctor(std::cout);
class A;
std::map<int, A&(*)()> m;

class A
{
protected:
	int id = 0;
public:
	virtual ~A() { std::cout << "~A()" << std::endl; };

	virtual void init() = 0;
	virtual void final() = 0;
};

class B : public Singleton<B, SingletonMode::Hungry>, public A
{
public:
	B()
	{
		m.insert(std::make_pair(1, getInst));
		std::cout << "B()" << std::endl;
	}

	~B() 
	{ 
		std::cout << "~B()" << std::endl; 
	}

	void init()
	{
		std::cout << "init B" << std::endl;
	}

	void final()
	{
		delMe();
		std::cout << "final B" << std::endl;
	}

	static A& getInst() { return getMe(); }
};

class C
{
public:
	virtual void init() { cout << "C" << endl; }
};

class D
{
public:
	virtual void pD() { cout << "D" << endl; }
};

class E : public C, public D
{
public:
	void init() { cout << "E" << endl; }
};

int main()
{
	for (std::map<int, A& (*)()>::iterator it = m.begin(); it != m.end(); ++it)
	{
		if (it->second)
			it->second().init();
	}

	for (std::map<int, A& (*)()>::iterator it = m.begin(); it != m.end(); ++it)
	{
		if (it->second)
			it->second().final();
	}


	return 0;
}
