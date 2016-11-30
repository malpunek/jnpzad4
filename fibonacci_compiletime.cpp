#include <tuple>
#include <utility>
#include <type_traits>
#include <iostream>

template<int n>
class fib {
	public:
		const static long long val = fib<n-1>::val + fib<n-2>::val;
};

template <>
class fib<0> {
	public:
		const static long long val = 0;
};

template <>
class fib<1> {
	public:
		const static long long val = 1;
};

template <typename T>
struct container;

template <int... Is>
struct container<std::integer_sequence<int, Is...>> {
    using type = std::tuple< fib<Is>... >;
};

int main()
{
	constexpr int n = 80;
	//const fib<n> qq;
    using X = container<std::make_integer_sequence<int, n> >::type;//remove_last_n::type;
	constexpr int war = std::tuple_element<20, X>::type::val;
	//std::cout<< war << std::endl;
	static_assert(war == 6765, "types do not match");
    //static_assert(std::is_same<X, int>::value, "types do not match");
}
