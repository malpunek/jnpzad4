#ifndef MONSTER_H
#define MONSTER_H
#include <cassert>
#include <type_traits>
#include "citizen.h"

const char VAMPIRE_N[] = "Vampire";
const char MUMMY_N[] = "Mummy";
const char ZOMBIE_N[] = "Zombie";

template<typename T,
         const char* nameString,
         typename TypeTest = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
struct Monster {
    private:
        T health_;
        T attackPower_;
        constexpr static const char* name_ = nameString;
    public:
        Monster() = delete;
        Monster(T health, T attackPower)
            : health_(health)
            , attackPower_(attackPower)
        {}

        typedef T valueType;

        T getHealth() const {
            return health_;
        }
        T getAttackPower() const {
            return attackPower_;
        }
        const char* getName() {
            return name_;
        }
        void takeDamage(T damage) {
            if (damage > health_)
                health_ -= health_;
            else
                health_ -= damage;
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