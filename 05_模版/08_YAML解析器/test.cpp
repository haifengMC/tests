#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <map>
#include <set>

#include "test.h"
#include "hYamlEx.h"
#include "hTest.h"
#include "hSingleton.h"

using namespace std;

TEST_INIT(Tst, testAll)

#define NODE_TEST(X)\
	{\
		YAML::Node node; \
		node = X; \
		cout << node << endl;\
		cout << endl;\
	}
#define NODEEX_TEST(X)\
	{\
		YAML::NodeEx node; \
		node = X; \
		cout << node << endl;\
		cout << endl;\
	}

TEST(Tst, Tst1)
{
	NODE_TEST(1);
	NODE_TEST("hello");
	string s = "hello";
	NODE_TEST(s);
	char cArr[] = "hello";
	NODE_TEST(cArr);
	NODE_TEST('a');
	NODE_TEST(1.1f);
	NODE_TEST(1.6);
	array<int, 4> ar = { 1,2,3,4 };
	NODE_TEST(ar);
	ar = { 1,2,3 };
	NODE_TEST(ar);
	map<string, string> m1{ {"peter", "shy"}, {"jone", "happy"}, {"lucy", "hello"}, };
	NODE_TEST(m1);
}

class A
{
public:
	YAML::Node node;
	A() {}
	A(const YAML::Node& node) : node(node) {}

	operator YAML::Node&() { return node; }

	template<typename T, size_t N>
	YAML::Node& operator=(const T(&rhs)[N])
	{
		for (const T& element : rhs)
			node.push_back(element);
		return node;
	}
};

TEST(Tst, Tst2)
{
	A a;
	a = { 1,2,3 };
	cout << a.node << endl;
}

class B : public YAML::Node
{
public:
	template<typename T, size_t N>
	B& operator=(const T(&rhs)[N])
	{
		for (const T& element : rhs)
			this->push_back(element);
		return *this;
	}
	
};

TEST(Tst, Tst3)
{
	B b;
	b = { 1,2,3 };
	cout << b << endl;
}

TEST(Tst, Tst4)
{
	NODEEX_TEST(1);
	NODEEX_TEST("hello");
	string s = "hello";
	NODEEX_TEST(s);
	char cArr[] = "hello";
	NODEEX_TEST(cArr);
	NODEEX_TEST('a');
	NODEEX_TEST(1.1f);
	NODEEX_TEST(1.6);
	array<int, 4> ar = { 1,2,3,4 };
	NODEEX_TEST(ar);
	ar = { 1,2,3 };
	NODEEX_TEST(ar);
	map<string, string> m1{ {"peter", "shy"}, {"jone", "happy"}, {"lucy", "hello"}, };
	NODEEX_TEST(m1);
	int a[] = { 1, 2, 3 };
	NODEEX_TEST(a);
}

TEST(Tst, Tst5)
{
	//map<string, string> m1{ {"peter", "shy"}, {"jone", "happy"}, {"lucy", "hello"}, };
	//YAML::NodeEx node1 = { {"peter", 2}, {"jone", 4} };
	//cout << node1 << endl;

	YAML::NodeEx node1 =
	{
		YAML::NodeEx("peter",
		{
			YAML::NodeEx("sex", "male")("123"),
			YAML::NodeEx("hight", 175),
			YAML::NodeEx("pos", { 0.3f, 0.6f }, YAML::EmitterStyle::Flow),
		}),
		YAML::NodeEx("jone", {1, 2, 3, 4})
	};

	cout << node1 << endl;
	YAML::NodeEx node2 = { {1, 2}, {3, 4, 5} };
	cout << node2 << endl;

}

TEST(Tst, Tst6)
{
	YAML::NodeEx node;
	if (!("Tst6.1.yml" >> node))
		return;
	
	node["peter"]["sex"] = "female";
	node["peter"]["pos"][1] = 1.5;
	cout << node["jone"][0].as<bool>() << endl;
	cout << node["jone"][1].as<double>() << endl;
	cout << node["jone"][2].as<string>() << endl;
	cout << node["jone"][3].as<string>() << endl;
	if (!("Tst6.2.yml" << node))
		return;
	cout << node << endl;
}

#undef NODE_TEST
#undef NODEEX_TEST