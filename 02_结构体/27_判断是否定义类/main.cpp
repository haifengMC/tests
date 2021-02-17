#include <iostream>

using namespace std;

struct B { virtual ~B() {} };
//struct A : public B {};
//struct A {};
struct A;

namespace detail {

	template <class T>
	std::true_type detect_is_polymorphic(
		decltype(static_cast<T*>(nullptr))
	);
	template <class T>
	std::false_type detect_is_polymorphic(...);

} // namespace detail

template <class T>
struct isDefine : decltype(detail::detect_is_polymorphic<T>(nullptr)) {};

int main()
{
	cout << is_class<A>::value << endl;
	//cout << is_polymorphic<A>::value << endl;
	cout << isDefine<A>::value << endl;
	return 0;
}