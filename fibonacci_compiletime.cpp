#include <tuple>
#include <utility>
#include <type_traits>
#include <iostream>

template<int n>
class fib {
	public:
		const long long value;
		const static long long val = fib<n-1>::val + fib<n-2>::val;
		constexpr fib() : value(val) {};
};

template <>
class fib<0> {
	public:
		const static long long val = 0;
		constexpr fib(){};
};

template <>
class fib<1> {
	public:
		const static long long val = 1;
		constexpr fib(){};
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
	std::array()

    using X = container<std::make_integer_sequence<int, n> >::type;
	constexpr int war = std::tuple_element<20, X>::type::val;
	static_assert(war == 6765, "Wrong number");
}
