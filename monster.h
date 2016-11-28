#ifndef MONSTER_H
#define MONSTER_H
#include <cassert>
#include <typeinfo>
#include <type_traits>
#include "citizen.h"

template<typename T,
         typename TypeTest = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
struct Monster {
    private:
        T health_;
        T attackPower_;
    public:
        Monster() = delete;
        Monster(T health, T attackPower)
            : health_(health)
            , attackPower_(attackPower)
        {}

        typename T valueType;

        T getHealth() const {
            return health_;
        }
        T getAttackPower() const {
            return attackPower_;
        }
        void takeDamage(T damage) {
            if (damage > health_)
                health_ -= health_;
            else
                health_ -= damage;
        }
};

template<typename T>
using Vampire = Monster<T>;

template<typename T>
using Zombie = Monster<T>;

template<typename T>
using Mummy = Monster<T>;

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
