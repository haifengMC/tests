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
			YAML::NodeEx("pos", { 0.3f, 0.6f })(YAML::EmitterStyle::Flow),
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

struct CfgData
{
	struct Mark
	{
		std::list<std::string> title;
		YAML::EmitterStyle::value style;
		std::string tag;
		Mark(const std::list<std::string>& title,
			const YAML::EmitterStyle::value& style,
			const std::string& tag) : title(title), style(style), tag(tag) {}
	};

	virtual bool loadCfg() = 0;
	virtual bool saveCfg() = 0;

	CfgData(const std::string& fileName) : fileName(fileName) {}

protected:
	std::string fileName;
	std::list<Mark> marks;

	bool checkMarks(const YAML::NodeEx& node, std::list<std::string> title = std::list<std::string>());
	bool setMarks(YAML::NodeEx& node);
private:
	bool addMark(const YAML::NodeEx& node, const std::list<std::string>& title);
};

bool CfgData::checkMarks(const YAML::NodeEx& node, std::list<std::string> title)
{
	addMark(node, title);
	switch (node.Type())
	{
	case YAML::NodeType::Undefined:
	case YAML::NodeType::Null:
	case YAML::NodeType::Scalar:
		break;
	case YAML::NodeType::Sequence:
		{
			title.push_back("");
			size_t count = 0;
			for (YAML::const_iterator it = node.begin(); it != node.end(); ++it, ++count)
			{
				std::string buf = std::to_string(count);
				title.back().swap(buf);
				checkMarks(YAML::Node(*it), title);
			}
		}
		break;
	case YAML::NodeType::Map:
		title.push_back("");
		for (YAML::const_iterator it = node.begin(); it != node.end(); ++it)
		{
			std::string buf = it->first.Scalar();
			title.back().swap(buf);
			checkMarks(it->second, title);
		}
		break;
	default:
		break;
	}

	return true;
}

bool CfgData::setMarks(YAML::NodeEx& node)
{
	for (const Mark& mark: marks)
	{
		YAML::NodeEx n = node;
		for (const std::string& tt : mark.title)
			n.reset(n[tt]);

		n.SetStyle(mark.style);
		n.SetTag(mark.tag);
	}

	return true;
}

bool CfgData::addMark(const YAML::NodeEx& node, const std::list<std::string>& title)
{
	if (YAML::EmitterStyle::Default == node.Style() && node.Tag() == "?")
		return false;

	Mark m(title, node.Style(), node.Tag());
	marks.push_back(m);

	return true;
}

struct MapCfgData
{
	virtual const size_t& index() const = 0;
};

struct PeterCfg
{
	size_t idx = 0;
	std::string sex = "";
	int hight = 0;
	float pos[2] = {};

};

template <>
struct YAML::convert<PeterCfg> {
	static Node encode(const PeterCfg& rhs) 
	{
		NodeEx node(NodeType::Map);
		node(IOType::PutOut);
		node["idx"] & rhs.idx;
		node["sex"] & rhs.sex;
		node["hight"] & rhs.hight;
		node["pos"] & rhs.pos;
		return node; 
	}
	static bool decode(const Node& node, PeterCfg& rhs) 
	{
		if (!node.IsMap())
			return false;
		NodeEx nodeEx = node;
		nodeEx(IOType::PutIn);
		nodeEx["idx"] & rhs.idx;
		nodeEx["sex"] & rhs.sex;
		nodeEx["hight"] & rhs.hight;
		nodeEx["pos"] & rhs.pos;
		return true; 
	}
};

struct Tst7CfgData : public CfgData
{
	PeterCfg peter;
	std::vector<std::string> jone;

	Tst7CfgData(const std::string& fileName) :CfgData(fileName) {}
	bool loadCfg()
	{
		YAML::NodeEx node;
		if (!(fileName >> node))
			return false;
		node(YAML::IOType::PutIn);
		checkMarks(node);

		node["peter"] & peter;
		node["jone"] & jone;

		return true;
	}
	bool saveCfg()
	{
		YAML::NodeEx node;
		node(YAML::IOType::PutOut);

		node["peter"] & peter;
		node["jone"] & jone;

		setMarks(node);
		return fileName << node;
	}


};

TEST(Tst, Tst7)
{
	//YAML::NodeEx node;
	//node["peter"] = { 1, 2, 3 };
	//node["trace"] = "hello";
	//node["lucy"] = 10;
	//cout << node << endl;
	Tst7CfgData cfg("Tst7.yml");
	cfg.loadCfg();
	cout << cfg.peter.sex << endl;
	cout << cfg.jone[3] << endl;
	cfg.peter.hight = 185;
	cfg.saveCfg();
}

TEST(Tst, Tst8)
{
	{
		YAML::NodeEx node = 1;
		cout << node << "_" << node.Type() << "_" << node.Style() << "_" << node.Tag() << endl;
		node.SetStyle(YAML::EmitterStyle::Flow);
		node.SetTag("hello");
		cout << node << "_" << node.Type() << "_" << node.Style() << "_" << node.Tag() << endl;

	}
	{
		YAML::NodeEx node;
		YAML::NodeEx node_1 = 1;
		node_1.SetStyle(YAML::EmitterStyle::Flow);
		node_1.SetTag("hello");
		node["peter"] = node_1;
		YAML::NodeEx node_2 = { 1, 2, 3 };
		node_2.SetTag("hello");
		node["lucy"] = node_2;
		cout << node << "_" << node.Type() << "_" << node.Style() << "_" << node.Tag() << endl;
		node.SetTag("hello");
		YAML::NodeEx _node_2 = node;
		_node_2.reset(_node_2["lucy"]);
		_node_2.SetStyle(YAML::EmitterStyle::Flow);
		cout << node << "_" << node.Type() << "_" << node.Style() << "_" << node.Tag() << endl;
		node.SetStyle(YAML::EmitterStyle::Flow);
		cout << node << "_" << node.Type() << "_" << node.Style() << "_" << node.Tag() << endl;

	}
}

#define  CFG_MEM(type, ...) COMB(EXPAND(CUTARGS_B(3, type, ##__VA_ARGS__, type())), COMMA_M(1))
#define  CFG_ARR(type, va, N) type, va, {}, N

#define CFG_STRUCT_F1(n, type, va, init, size) type  SWITCH_CASE(EQ(size, 1), va[size], va) = init
#define CFG_STRUCT_F2(n, type, va, init, size) node[TO_STRING(va)] & rhs.va
#define CFG_STRUCT_F3(n, type, va, init, size) node[TO_STRING(va)] & va
#define CFG_STRUCT(className, ...) \
	struct className\
	{\
		REPEAT_F_SEP(CFG_STRUCT_F1, 4, SEM_M, ##__VA_ARGS__);\
	};\
	template <>\
	struct YAML::convert<className> {\
		static Node encode(const className& rhs)\
		{\
			NodeEx node(NodeType::Map);\
			node(IOType::PutOut);\
			REPEAT_F_SEP(CFG_STRUCT_F2, 4, SEM_M, ##__VA_ARGS__); \
			return node;\
		}\
		static bool decode(const Node& n, className& rhs)\
		{\
			if (!n.IsMap())\
				return false;\
			NodeEx node = n;\
			node(IOType::PutIn); \
			REPEAT_F_SEP(CFG_STRUCT_F2, 4, SEM_M, ##__VA_ARGS__); \
			return true;\
		}\
	};

#define CFG_DATA(className, ...) \
	struct className : public CfgData\
	{\
		REPEAT_F_SEP(CFG_STRUCT_F1, 4, SEM_M, ##__VA_ARGS__); \
		className(const std::string& fileName) :CfgData(fileName) {}\
		bool loadCfg()\
		{\
			YAML::NodeEx node;\
			if (!(fileName >> node))\
				return false;\
			node(YAML::IOType::PutIn);\
			checkMarks(node);\
			REPEAT_F_SEP(CFG_STRUCT_F3, 4, SEM_M, ##__VA_ARGS__); \
			return true;\
		}\
		bool saveCfg()\
		{\
			YAML::NodeEx node;\
			node(YAML::IOType::PutOut);\
			REPEAT_F_SEP(CFG_STRUCT_F3, 4, SEM_M, ##__VA_ARGS__); \
			setMarks(node);\
			return fileName << node;\
		}\
	};


CFG_STRUCT(Tst9PeterCfg,
	CFG_MEM(size_t, idx),
	CFG_MEM(std::string, sex),
	CFG_MEM(int, hight),
	CFG_ARR(float, pos, 2));
CFG_DATA(Tst9DataCfg,
	CFG_MEM(Tst9PeterCfg, peter),
	CFG_MEM(std::vector<std::string>, jone));


TEST(Tst, Tst9)
{
	Tst9DataCfg cfg("Tst9.yml");
	cfg.loadCfg();
	cout << cfg.peter.idx << " " << cfg.peter.sex << " " << cfg.peter.hight << " " << cfg.peter.pos[0] << " " << cfg.peter.pos[1] << endl;
	for (std::string& s : cfg.jone)
		cout << s << endl;
	cfg.peter.idx = 1111;
	cfg.peter.sex = "aaaa";
	cfg.peter.hight = 2222;
	cfg.saveCfg();
}

#undef NODE_TEST
#undef NODEEX_TEST

