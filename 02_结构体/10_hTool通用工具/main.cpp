#include "global.h"
#include "hTool.h"
#include "hTest.h"

using namespace std;
using namespace hTool;

TEST_INIT(Tst, testAll)

struct A 
{ 
	A() = default;
	A(const A&) { cout << "copy A" << endl; }
	A(A&&) = delete;
};
struct B 
{ 
	B() = default; 
	B(int) {}
	B(const B&) = delete; 
	B(const B&&) { cout << "move B" << endl; }
};
struct C { C(const C&) = default; C(C&&) = default; };
struct D { D(const D&) = delete; D(D&&) = delete; };
struct E
{
	E() = default;
	E(const E&) = delete;
	E(E&&) { cout << "move E" << endl; }
};

TEST(Tst, 判断构造器是否可构造)
{
	cout << "A: "
		"def " << isConstructible<A>(Constructible::Default) << ", "
		"cpy " << isConstructible<A>(Constructible::Copy) << ", "
		"mov " << isConstructible<A>(Constructible::Move) << endl;
	cout << "B: "
		"def " << isConstructible<B>(Constructible::Default) << ", "
		"cpy " << isConstructible<B>(Constructible::Copy) << ", "
		"mov " << isConstructible<B>(Constructible::Move) << endl;
	cout << "C: "
		"def " << isConstructible<C>(Constructible::Default) << ", "
		"cpy " << isConstructible<C>(Constructible::Copy) << ", "
		"mov " << isConstructible<C>(Constructible::Move) << endl;
	cout << "D: "
		"def " << isConstructible<D>(Constructible::Default) << ", "
		"cpy " << isConstructible<D>(Constructible::Copy) << ", "
		"mov " << isConstructible<D>(Constructible::Move) << endl;
}

template <typename T>
void insert_1(map<int, remove_reference_t<T>>& m, T t)
{
	cout << __FUNCTION__ << endl;
	m.insert(make_pair(1, move(t)));
}
template <typename T>
void insert_2(map<int, remove_reference_t<T>>& m, const T& t)
{
	cout << __FUNCTION__ << endl;
	m.insert(make_pair(2, t));
}
template <typename T>
void insert_2(map<int, remove_reference_t<T>>& m, T&& t)
{
	cout << __FUNCTION__ << endl;
	m.insert(make_pair(2, move(t)));
}
template <typename T>
void insert_3(map<int, T>& m, const T& t)
{
	cout << __FUNCTION__ << endl;
	m.insert(make_pair(3, move(t)));
}
template <typename T>
void insert_4(map<int, T>& m, T&& t)
{
	cout << __FUNCTION__ << " T&& t" << endl;
	m.insert(make_pair(4, move(t)));
}
template <typename T>
void insert_4(map<int, T>& m, T& t)
{
	cout << __FUNCTION__ << " T& t" << endl;
	m.insert(make_pair(4, move(t)));
}
template <typename T>
void insert_4(map<int, T>& m, const T& t)
{
	cout << __FUNCTION__ << " const T& t" << endl;
	m.insert(make_pair(4, t));
}


TEST(Tst, 将元素正确拷贝或移入容器)
{
	A a;
	map<int, A> mA;
	B b;
	map<int, B> mB;

	insert_1(mA, a);
	insert_1(mB, move(b));
	cout << string(10, '-') << endl;
	insert_2(mA, a);
	insert_2(mB, move(b));
	cout << string(10, '-') << endl;
	insert_3(mA, a);
	insert_3(mB, move(b));
	cout << string(10, '-') << endl;
	insert_4(mA, a);
	cout << string(3, '.') << endl;
	insert_4(mB, b);
	cout << string(3, '.') << endl;
	insert_4(mB, move(b));
}

int main()
{
	testAll();

	return 0;
}