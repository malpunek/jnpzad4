#include <cstdio>
#include <algorithm>
using namespace std;

constexpr long long fibb(int n){
	return  n <= 1 ? n : fibb(n-1) + fibb(n-2);
}

template<int n>
class fib {
	public:
		constexpr static long long val = fib<n-1>::val + fib<n-2>::val;
};

template <>
class fib<0> {
	public:
		constexpr static long long val = 0;
};

template <>
class fib<1> {
	public:
		constexpr static long long val = 1;
};


int main(){
	constexpr int n = 80;
	constexpr long long cc = fibb(n);
	constexpr fib<n> qq;
	printf("%lld\n%lld\n", cc, qq.val);
	return 0;
	}
