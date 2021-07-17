/*
** EPITECH PROJECT, 2020
** cpp_d08_2019 [WSL: Ubuntu]
** File description:
** Carrier
*/

#pragma once

#define ABS(a) (a > 0 ? a : -a)

#include "Droid.hpp"

class Carrier {
    public:
        Carrier(const std::string &id="");
        ~Carrier();

        std::string getId() const;
        size_t getEnergy() const;
        size_t getAttack() const;
        size_t getToughness() const;
        size_t getSpeed() const;
        void setId(const std::string &);
        void setEnergy(const size_t);
        void setSpeed(const size_t);

        Carrier &operator<<(size_t &);
        Carrier &operator<<(Droid *&);
        Carrier &operator>>(Droid *&);
        Droid *&operator[](const size_t);
        Droid *operator[](const size_t) const;
        bool operator()(const int, const int);
        Carrier &operator~();

    protected:
    private:
        std::string Id;
        size_t Energy;
        const size_t Attack;
        const size_t Toughness;
        size_t Speed;
        Droid *Droids[5];
};

std::ostream &operator<<(std::ostream &os, Carrier const &c);