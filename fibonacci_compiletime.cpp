#include <cstdio>
#include <algorithm>
using namespace std;


template<int n>
const long long fib(){
	return fib<n-1>() + fib<n-2>();
	}

template<>
const long long fib<0>(){
	return 0;
}

template<>
const long long fib<1>(){
	return 1;
}
int main(){
	int n;
	printf("%lld\n", fib<60>());
	return 0;
	}
