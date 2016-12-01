#include <algorithm>
#include <iostream>

template<int N>
struct Fibo {
    constexpr Fibo() : array() {
        array[0] = 1;
        array[1] = 1;
        for (auto i = 2; i != N; ++i)
            array[i] = array[i - 1] + array[i - 2]; 
    }

    long long unsigned array[N];

    bool isFibo(long long unsigned x) const {
        return std::binary_search(array, array + N, x);
    }
};

int main() {
    constexpr auto fibo = Fibo<12>();
    std::cout << fibo.isFibo(13) << std::endl;
    std::cout << fibo.isFibo(10) << std::endl;
    return 0;
}

