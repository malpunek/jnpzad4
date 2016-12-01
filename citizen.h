#ifndef CITIZEN_H
#define CITIZEN_H
#include <cassert>
#include <type_traits>

template <typename T,
         unsigned age_lower,
         unsigned age_upper,
         bool can_attack,
         typename TypeTest = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
struct Citizen {
    private:
        T health;
        T age;
        T attack_power;
    public:
        Citizen() = delete;

        template <typename Q = T>
        Citizen(typename std::enable_if<can_attack, Q>::type health, Q age, Q attack_power)
            : health(health)
            , age(age)
            , attack_power(attack_power)
        {
            assert(age >= age_lower);
            assert(age <= age_upper);
        }

        template <typename Q = T>
        Citizen(typename std::enable_if<!can_attack, Q>::type health, Q age)
            : health(health)
            , age(age)
        {
            assert(age >= age_lower);
            assert(age <= age_upper);
        }

        T getHealth() const { return health; }
        T getAge() const { return age; }

        template <typename Q = T>
        typename std::enable_if<can_attack, Q>::type getAttackPower() const { return attack_power; }

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

