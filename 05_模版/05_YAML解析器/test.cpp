#include "test.h"
#include "vmacro.h"

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include "yaml-cpp/yaml.h"

using namespace std;

#define TEST_FUNC_BEG(X) void X(){ cout << "------" << endl; cout << TO_STRING(X) << endl;
#define TEST_FUNC_END() }

void printCfg(const YAML::Node& config, byte deep = 0)
{
	auto typeNm = [](const YAML::NodeType::value& t) 
	{ 
		const char* typeName[] = { "undef", "nul", "sclr", "seq", "map" };
		return typeName[t];
	};

	switch (config.Type())
	{
	case YAML::NodeType::Undefined:
		break;
	case YAML::NodeType::Null:
		cout << "<Null>" << endl;
		break;
	case YAML::NodeType::Scalar:
		cout << config.as<string>() << endl;
		break;
	case YAML::NodeType::Sequence:
		for (YAML::const_iterator it = config.begin(); it != config.end(); ++it)
		{
			cout << string(deep, ' ') << typeNm(it->Type()) << "." << it->Style() << ": ";
			if (it->IsMap() || it->IsSequence())
				cout << endl;
			printCfg(*it, deep + 1);
		}
		break;
	case YAML::NodeType::Map:
		for (YAML::const_iterator it = config.begin(); it != config.end(); ++it)
		{
			cout << string(deep, ' ') << it->first.as<string>() << "." << typeNm(it->second.Type()) << "." << it->second.Style() << ": ";
			if (it->second.IsMap() || it->second.IsSequence())
				cout << endl;
			printCfg(it->second, deep + 1);
		}
		break;
	default:
		break;
	}
}

TEST_FUNC_BEG(test1)

YAML::Node config = YAML::LoadFile("test1.yml");
cout << config.Type() << endl;
cout << "name:" << "[" << config["name"].Type() << "]" << config["name"].as<string>() << endl;
cout << "sex:" << "[" << config["sex"].Type() << "]" << config["sex"].as<string>() << endl;
cout << "age:" << "[" << config["age"].Type() << "]" << config["age"].as<int>() << endl;

cout << endl;
cout << "skills:" << "[" << config["skills"].Type() << "]" << endl;
cout << "skills c++:" << "[" << config["skills"]["c++"].Type() << "]" << config["skills"]["c++"].as<int>() << endl;
cout << "skills java:" << "[" << config["skills"]["java"].Type() << "]" << config["skills"]["java"].as<int>() << endl;
cout << "skills android:" << "[" << config["skills"]["android"].Type() << "]" << config["skills"]["android"].as<int>() << endl;
cout << "skills python:" << "[" << config["skills"]["python"].Type() << "]" << config["skills"]["python"].as<int>() << endl;

cout << endl;
for (YAML::const_iterator it = config["skills"].begin(); it != config["skills"].end(); ++it)
	cout << it->first.as<string>() << ":" << "[" << it->second.Type() << "]" << it->second.as<int>() << endl;

TEST_FUNC_END(test1)

TEST_FUNC_BEG(test2)

YAML::Node config = YAML::LoadFile("test1.yml");
printCfg(config);

TEST_FUNC_END(test2)

TEST_FUNC_BEG(test3)

YAML::Node cfg1 = YAML::Load("[1,2,3,4]");
cout << " Type: " << cfg1.Type() << endl;

YAML::Node cfg2 = YAML::Load("1");
cout << " Type: " << cfg2.Type() << endl;

YAML::Node cfg3 = YAML::Load("{'id':1,'degree':'senior'}");
cout << " Type: " << cfg3.Type() << endl;

TEST_FUNC_END(test3)

TEST_FUNC_BEG(test4)

ofstream fout("test4.yml");
YAML::Node config = YAML::LoadFile("test1.yml");

config["score"] = 99;
config["age"] = 19;
config["seq"].push_back(1);
config["seq"].push_back(2);
config["seq"].push_back(3);
config["seq"].SetStyle(YAML::EmitterStyle::Block);
config["scl"].push_back("a");
config["scl"].push_back("b");
config["scl"].SetStyle(YAML::EmitterStyle::Flow);
YAML::Node tmpNode;
tmpNode["a"] = 1;
tmpNode["b"] = 2;
config["map1"] = tmpNode;
config["map1"].SetStyle(YAML::EmitterStyle::Flow);

printCfg(config);
fout << config;

fout.close();

TEST_FUNC_END(test4)

TEST_FUNC_BEG(test5)
YAML::Node config = YAML::LoadFile("test5.yml");
cout << config["key"] << endl;
cout << config["key"][0] << " " << config["key"][1] << " " << config["key"][2] << " [" << config["key"][20] << "] " << config["key"][3] << " " << config["key"][4] << endl;
printCfg(config);
TEST_FUNC_END(test5)


#undef TEST_FUNC_BEG
#undef TEST_FUNC_END
