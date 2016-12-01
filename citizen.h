#ifndef CITIZEN_H
#define CITIZEN_H
#include <cassert>
#include <type_traits>

template <typename T,
         unsigned ageLower,
         unsigned ageUpper,
         bool canAttack,
         typename TypeTest = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
struct Citizen {
    private:
        T health;
        T age;
        T attackPower;
    public:
        Citizen() = delete;

        template <typename Q = T>
        Citizen(typename std::enable_if<canAttack, Q>::type health, Q age, Q attackPower)
            : health(health)
            , age(age)
            , attackPower(attackPower)
        {
            assert(age >= ageLower);
            assert(age <= ageUpper);
        }

        template <typename Q = T>
        Citizen(typename std::enable_if<!canAttack, Q>::type health, Q age)
            : health(health)
            , age(age)
        {
            assert(age >= ageLower);
            assert(age <= ageUpper);
        }

        T getHealth() const { return health; }
        T getAge() const { return age; }

        template <typename Q = T>
        typename std::enable_if<canAttack, Q>::type getAttackPower() const { return attackPower; }

        bool isAlive() const { return health != health - health; }
        void takeDamage (T damage) {
            if (damage > health)
                health -= health;
            else
                health -= damage;
        }

};

template <typename T>
using Adult = Citizen<T, 18, 100, false>;

template <typename T>
using Teenager = Citizen<T, 11, 17, false>;

template <typename T>
using Sheriff = Citizen<T, 18, 100, true>;
#endif

