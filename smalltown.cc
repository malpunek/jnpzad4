#include <iostream>
#include <tuple>
#include <algorithm>
#include <cstddef>
#include <type_traits>
#include "citizen.h"
#include "monster.h"

constexpr const size_t FIB_MAX = 40;
const char* CITIZENS_WON = "CITIZENS WON";
const char* MONSTER_WON = "MONSTER WON";
const char* DRAW = "DRAW";

template<size_t N>
struct Fibo {
    constexpr Fibo() : array() {
        array[0] = 1;
        array[1] = 1;
        for (size_t i = 2; i < N; ++i)
            array[i] = array[i - 1] + array[i - 2]; 
    }

    long long unsigned array[N];

    bool isFibo(long long unsigned x) const {
        return std::binary_search(array, array + N, x);
    }
};

template<typename M,
         typename U,
         U t0,
         U t1,
         typename... C>
class SmallTown{
    private:
        static_assert(t0 <= t1, "Starting time greater than time limit!");
        
        typedef std::tuple<C...> C_type;
        typedef M M_type;
        C_type citizens;
        M_type monster;
        U current_time = t0, max_time = t1;

        bool isCityDead() {
            return countAliveCitizens(std::index_sequence_for<C...> {}) == 0;
        }

        template<typename T>
        size_t counter(T first) {
            return first.isAlive();
        }

        template<typename T, typename... Ts>
        size_t counter(T first, Ts... rest) {
            return counter(rest...) + first.isAlive();
        }

        template<std::size_t... Is>
        size_t countAliveCitizens(std::index_sequence<Is...>) {
            return counter(std::get<Is>(citizens)...);
        }

        template<typename T>
        void attacker(T first) {
            attack(monster, first);
        }
        
        template<typename T, typename ... Ts>
        void attacker(T first, Ts ... rest) {
            attack(monster, first);
            attacker(rest...);
        }

        template<std::size_t... Is>
        void attackEveryone(std::index_sequence<Is...>) {
            attacker(std::get<Is>(citizens)...);
        }
    public:
        SmallTown(M m, C... c)
            : citizens(c...)
            , monster(m)
        {}        

        void tick(U timeStep) {
            constexpr static auto fibo = Fibo<FIB_MAX>();

            if (!monster.isAlive())
                std::cout << (isCityDead() ? DRAW : CITIZENS_WON) << std::endl;
            else if (isCityDead())
                std::cout << MONSTER_WON << std::endl;
            else if (fibo.isFibo(current_time))
                attackEveryone(std::index_sequence_for<C...>{});

            while (current_time + timeStep > max_time){
                timeStep -= max_time - current_time;
                current_time = current_time - current_time;
            }
            current_time += timeStep;
        }

        std::tuple<std::string, typename M::valueType, size_t> getStatus(){
            return make_tuple(std::string(monster.getName()), monster.getHealth(),
                    countAliveCitizens(std::index_sequence_for<C...>{}));
        }

};

