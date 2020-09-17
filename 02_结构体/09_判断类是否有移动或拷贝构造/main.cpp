#include <iostream>
#include <type_traits>

using namespace std;

struct A { A(const A&) = default; A(A&&) = delete; };
struct B { B(const B&) = delete; B(B&&) = default; };
struct C { C(const C&) = default; C(C&&) = default; };
struct D { D(const D&) = delete; D(D&&) = delete; };

int main()
{
	cout << "A: "
		"copy " << is_copy_constructible<A>::value << ", "
		"move " << is_move_constructible<A>::value << endl;
	cout << "B: "
		"copy " << is_copy_constructible<B>::value << ", "
		"move " << is_move_constructible<B>::value << endl;
	cout << "C: "
		"copy " << is_copy_constructible<C>::value << ", "
		"move " << is_move_constructible<C>::value << endl;
	cout << "D: "
		"copy " << is_copy_constructible<D>::value << ", "
		"move " << is_move_constructible<D>::value << endl;

	return 0;
}
