#ifndef CITIZEN_H
#define CITIZEN_H
#include <cassert>
#include <type_traits>

template <typename T,
         T ageLower,
         T ageUpper,
         bool canAttack,
         typename TypeTest = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
struct Citizen {
    private:
        T age_;
        T health_;
        T attackPower_;
    public:
        Citizen() = delete;

        template <typename Q = T>
        Citizen(Q health, typename std::enable_if<canAttack, Q>::type age, Q attackPower)
            : age_(age)
            , health_(health)
            , attackPower_(attackPower)
        {
            assert(age >= ageLower);
            assert(age <= ageUpper);
        }

        template <typename Q = T>
        Citizen(Q health, typename std::enable_if<!canAttack, Q>::type age)
            : age_(age)
            , health_(health)
        {
            assert(age >= ageLower);
            assert(age <= ageUpper);
        }

        T getHealth() const { return health_; }
        T getAge() const { return age_; }

        template <typename Q = T>
        typename std::enable_if<canAttack, Q>::type getAttackPower() const { return attackPower_; }

        void takeDamage (T damage) {
            if (damage > health_)
                health_ -= health_;
            else
                health_ -= damage;
        }
};


template <typename T>
using Adult = Citizen<T, 18, 100, false>;

template <typename T>
using Teenager = Citizen<T, 11, 17, false>;

template <typename T>
using Sheriff = Citizen<T, 18, 100, true>;
#endif
