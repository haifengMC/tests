#include "global.h"
#include "vjson.h"
#include "vtype.h"

struct Student : public JsonData {
	Student() : name(), age(), height(), canSwim() {}
	Student(const std::string name, unsigned age, double height, bool canSwim) :
		name(name), age(age), height(height), canSwim(canSwim)
	{}

	std::string name;
	unsigned age;
	float height;
	bool canSwim;
};

template <typename Archiver>
Archiver& operator&(Archiver& ar, Student& s) {
	ar.BindObject(s);
	ar.StartObject();
	ar["name"]& s.name;
	ar["age"]& s.age;
	ar["height"]& s.height;
	ar["canSwim"]& s.canSwim;
	return ar.EndObject();
}

std::ostream& operator<<(std::ostream& os, const Student& s) {
	return os << s.name << " " << s.age << " " << s.height << " " << s.canSwim;
}

void test1()
{
	std::string json;

	// Serialize
	{
		Student s("Lua", 9, 150.5, true);

		JsonWriter writer;
		writer& s;
		json = writer.GetString();
		std::cout << json << std::endl;
	}

	// Deserialize
	{
		Student s;
		JsonReader reader(json.c_str());
		reader& s;
		std::cout << s << std::endl;
	}
}

struct ShaderCfg : public JsonData
{
	ShaderCfg() {}
	ShaderCfg(GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b) : vertex(x, y), color(r, g, b) {}

	vec2 vertex;
	vec3 color;
};

template <typename Archiver>
Archiver& operator&(Archiver& ar, ShaderCfg& s) 
{
	ar.StartObject();
	ar["vertex"] & s.vertex;
	ar["color"] & s.color;
	return ar.EndObject();
}

std::ostream& operator<<(std::ostream& os, const ShaderCfg& s) 
{
	return os << s.vertex << " " << s.color;
}

void test2()
{
	std::string json;

	// Serialize
	{
		ShaderCfg s(0.5f, 0.6f, 1.0f, 0.0f, 1.0f);
		std::cout << s << std::endl;
		
		JsonWriter writer;
		writer& s;
		json = writer.GetString();
		std::cout << json << std::endl;
	}

	// Deserialize
	{
		ShaderCfg s;
		JsonReader reader(json.c_str());
		reader& s;
		std::cout << s << std::endl;
	}
}

void test3()
{
	JsonStream stream("ShaderCfg.json");
	// Serialize
	{
		ShaderCfg s(0.5f, 0.6f, 1.0f, 0.0f, 1.0f);
		
		JsonWriter writer;
		writer& s;
		stream << writer;
	}

	// Deserialize
	{
		ShaderCfg s;
		JsonReader reader;
		stream >> reader;
		reader& s;
		std::cout << s << std::endl;
	}
}

void test4()
{
	Student s("Lua", 9, 150.5, true);
	JsonWriter writer;
	s.addFilter("age");
	s.addFilter("height");
	s.delFilter("age");
	writer& s;
	std::string json = writer.GetString();
	std::cout << json << std::endl;
}

void test5()
{
	JsonStream stream("Student.json"); 
	JsonStream stream1("Student1.json");
	Student s;
	JsonReader reader;
	JsonWriter writer;

	stream >> reader;
	reader& s;

	writer& s;
	stream1 << writer;
}

Json::JsonRW& operator&(Json::JsonRW& ar, Student& s) {
	using namespace Json;
	return ar &
		begObj &
			mem("name", s.name) &
			mem("age", s.age) &
			mem("height", s.height) &
			mem("canSwim", s.canSwim) &
		endObj;
}

void test6()
{
	using namespace Json;
	Json::JsonRW rw;
	std::string json;
	{
		Student s("Lua", 9, 150.5, true);
		rw(Json::JsonRWMode::JsonRWMode_Write)(json) & s & end;
		std::cout << json << std::endl;
	}

	{
		Student s;
		rw(Json::JsonRWMode::JsonRWMode_Read)(json) & s & end;
		std::cout << s << std::endl;
	}
}

int main()
{
	//test1();
	//test2();
	//test3();
	//test4();
	//test5();
	test6();

	return 0;
}
