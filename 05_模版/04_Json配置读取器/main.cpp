#include "global.h"
#include "vjson.h"

struct Student {
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

int main()
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


	return 0;
}
