#include <cstdio>
#include <algorithm>
using namespace std;

constexpr long long fibb(int n){
	return  n <= 1 ? n : fibb(n-1) + fibb(n-2);
}

int main(){
	int n;
	constexpr long long cc = fibb(90);
	printf("%lld\n", cc);
	return 0;
	}
