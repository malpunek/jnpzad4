#include <cstdio>
#include <tuple>
#include <algorithm>
#include <cstddef>
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
        for (auto i = 2; i != N; ++i)
            array[i] = array[i - 1] + array[i - 2]; 
    }

    long long unsigned array[N];

    bool isFibo(long long unsigned x) const {
        return std::binary_search(array, array + N, x);
    }
};

template<typename M, typename U, U t0, U t1, typename ... C>
class SmallTown{
    private:
        typedef std::tuple<C...> C_type;
        typedef M M_type;
        C_type citizens;
        M_type monster;
        U current_time = t0, max_time = t1;

        bool isCityDead() {
            return countAliveCitizens(std::index_sequence_for<C...> {}) == 0;
        }

        template<typename T>
        size_t isAlive(T a_guy) {
            if (a_guy.getHealth() == a_guy.getHealth() - a_guy.getHealth())
                return 0;
            return 1;
        }

        template<typename T>
        size_t counter(T firster) {
            return isAlive(firster);
        }

        template<typename T, typename... Ts>
        size_t counter(T firster, Ts... lasts) {
            return counter(lasts...) + isAlive(firster);
        }

        template<std::size_t... Is>
        size_t countAliveCitizens(std::index_sequence<Is...>) {
            return counter(std::get<Is>(citizens)...);
        }

        template<typename T>
        void attacker(T firster) {
            attack(monster, firster);
        }
        
        template<typename T, typename ... Ts>
        void attacker(T firster, Ts ... lasts) {
            attack(monster, firster);
            attacker(lasts...);
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
                printf("%s\n", isCityDead() ? DRAW : CITIZENS_WON);
            else if (isCityDead())
               printf("%s\n", MONSTER_WON);    
            else {
                if (fibo.isFibo(current_time))
                    attackEveryone(std::index_sequence_for<C...>{});
            }

            while (current_time + timeStep > max_time){
                timeStep -= max_time - current_time;
                current_time = max_time - max_time;
            }
            current_time += timeStep;
        }

        std::tuple<std::string, typename M::valueType, size_t> getStatus(){
            return make_tuple(std::string(monster.getName()), monster.getHealth(),
                    countAliveCitizens(std::index_sequence_for<C...>{}));
        }

};

