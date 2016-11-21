#include <cstdio>
#include <algorithm>
using namespace std;

constexpr long long fibb(int n){
	return  n <= 1 ? n : fibb(n-1) + fibb(n-2);
}

/*
template<typename T, int n>
class fib {
	public:
		static T val;
		static T getVal(){
			return val;
			}
		static bool gotit=false;
		void compute(){
			if (gotit) return;
			fib<T, n-1> fst;
			fib<T, n-2> scd;
			fst.compute();
			scd.compute();
			val = fst.getVal() + scd.getVal();
			gotit = true;
		}
		fib(){}
	};

template<>
class fib<long long, 0>{
	public:
		static long long val;
		static long long getVal(){
			return 0;
		}
		void compute(){}
		fib(){
		}
};

template<>
class fib<long long, 1>{
	public:
		static long long val;
		static long long getVal(){
			return 1;
		}
		void compute(){}
		fib(){
		}
};
*/
int main(){
	int n;
/*	fib<long long, 5> fibbbb;
	fibbbb.compute();
	const long long kk = fibbbb.getVal();
	printf("%lld\n", kk);*/
	constexpr long long cc = fibb(90);
	printf("%lld\n", cc);
	return 0;
	}
