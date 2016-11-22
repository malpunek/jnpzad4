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


		//constexpr static fib<n-2> val2;	
int main(){
	int n;
	constexpr long long cc = fibb(90);
	constexpr fib<90> qq;
	printf("%lld\n%lld\n", cc, qq.val);
	return 0;
	}
