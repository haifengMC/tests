#include <iostream>
#include <fstream>
#include <map>
#include "test.pb.h"

using namespace std;

struct Test
{
	int _i = 0;
	std::map<int, Test> _m;

	void serialize(TestProto& proto) const;
	void unserialze(const TestProto& proto);
};
ostream& operator<<(ostream& os, const Test& t);

int main()
{
	Test t1;
	t1._i = 1;
	Test t2;
	t2._i = 2;
	Test t3;
	t3._i = 3;
	t1._m.insert(make_pair(t1._i, t1));
	t1._m.insert(make_pair(t2._i, t2));
	t3._m.insert(make_pair(t1._i, t1));
	t1._m.insert(make_pair(t3._i, t3));
	t2._m.insert(make_pair(t1._i, t1));
	cout << t1 << endl;
	TestProto proto;	
	t1.serialize(proto);
	std::fstream output("test.bin", std::ios::out | std::ios::trunc | std::ios::binary);
	proto.SerializePartialToOstream(&output);
	output.close();
	cout << proto.DebugString() << endl;
	t2.unserialze(proto);
	cout << t2 << endl;


	cout << t3 << endl;
	std::fstream input("test.bin", std::ios::in | std::ios::binary);
	proto.Clear();
	proto.ParseFromIstream(&input);
	input.close();
	t3.unserialze(proto);
	cout << t3 << endl;

	return 0;
}

void Test::serialize(TestProto& proto) const
{
	proto.set_i(_i);
	for (auto& pr : _m)
	{
		TestProto* pT = proto.add_t();
		pr.second.serialize(*pT);
	}
}
void Test::unserialze(const TestProto& proto)
{
	_i = proto.i();
	_m.clear();
	for (size_t i = 0; i < proto.t_size(); ++i)
	{
		Test t;
		t.unserialze(proto.t(i));
		_m.insert(make_pair(t._i, t));
	}
}

ostream& operator<<(ostream& os, const Test& t)
{
	os << "i:" << t._i << "{";
	bool first = true;
	for (auto& pr : t._m)
	{
		if (first) first = false;
		else os << ",";

		os << pr.second;
	}

	return os << "}";
}