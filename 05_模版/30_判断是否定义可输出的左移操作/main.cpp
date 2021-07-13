#include <utility>
#include <string>
#include <typeinfo>
#include <type_traits>
#include <iostream>

using namespace std;

template <typename Ty, typename = void>
struct IsPutOut { static constexpr bool value = false; };

template <class Ty>
struct IsPutOut<Ty, void_t<decltype(cout << declval<Ty>())>>
{
	static constexpr bool value = true;
};

struct A {};
struct B {};
ostream& operator<<(ostream& os, const A&) { return os << "A"; }

int main()
{
	cout << boolalpha;
	cout << IsPutOut<int>::value << endl;
	cout << IsPutOut<A>::value << endl;
	cout << IsPutOut<B>::value << endl;

	return 0;
}