#include "global.h"
#include "hTool.h"
#include "hTest.h"

using namespace std;
using namespace hTool;

TEST_INIT(Tst, testAll)

struct A { A(const A&) = default; A(A&&) = delete; };
struct B { B(const B&) = delete; B(B&&) = default; };
struct C { C(const C&) = default; C(C&&) = default; };
struct D { D(const D&) = delete; D(D&&) = delete; };

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

int main()
{
	testAll();

	return 0;
}