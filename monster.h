#ifndef MONSTER_H
#define MONSTER_H
#include <cassert>
#include <type_traits>
#include "citizen.h"

constexpr const char VAMPIRE_N[] = "Vampire";
constexpr const char MUMMY_N[] = "Mummy";
constexpr const char ZOMBIE_N[] = "Zombie";

template<typename T,
         const char* name_string,
         typename TypeTest = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
struct Monster {
    private:
        T health;
        T attack_power;
        constexpr static const char* name = name_string;
    public:
        Monster() = delete;
        Monster(T health, T attack_power)
            : health(health)
            , attack_power(attack_power)
        {}

        typedef T valueType;

        T getHealth() const { return health; }

        T getAttackPower() const { return attack_power; }

		bool isAlive() const { return health != health - health; }

        const char* getName() const { return name; }

        void takeDamage(T damage) {
            if (damage > health)
                health -= health;
            else
                health -= damage;
        }
};

template<typename T>
using Vampire = Monster<T, VAMPIRE_N>;

template<typename T>
using Zombie = Monster<T, ZOMBIE_N>;

template<typename T>
using Mummy = Monster<T, MUMMY_N>;

template<typename M, typename U>
void attack(M& monster, U& victim) {
    victim.takeDamage(monster.getAttackPower());
}

template<typename M, typename T>
void attack(M& monster, Sheriff<T>& victim) {
    victim.takeDamage(monster.getAttackPower());
    monster.takeDamage(victim.getAttackPower());
}
#endif
