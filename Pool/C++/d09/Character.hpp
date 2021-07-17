/*
** EPITECH PROJECT, 2020
** cpp_d09_2019 [WSL: Ubuntu]
** File description:
** Character
*/

#pragma once

#include <iostream>

class Character {
    public:
        enum AttackRange {
            CLOSE,
            RANGE
        };

        Character(const std::string &name, int level, const std::string &race="Human", const std::string &clas="Character", int pv=100, int mp=100, int str=5, int stam=5, int intel=5, int spi=5, int agi=5);
        ~Character();

        const std::string &getName() const;
        const std::string &getRace() const;
        const std::string &getClass() const;        
        int getLvl() const;
        int getPv() const;
        int getPower() const;
        int getStrength() const;
        int getStamina() const;
        int getIntelligence() const;
        int getSpirit() const;
        int getAgility() const;

        int CloseAttack();
        int RangeAttack();
        void Heal();
        void RestorePower();
        void TakeDamage(int damage);

        AttackRange Range;

    protected:
        const std::string Name;
        int Lvl;
        std::string Race;
        std::string Class;
        int MaxPv;
        int Pv;
        int MaxPower;
        int Power;
        int Strength;
        int Stamina;
        int Intelligence;
        int Spirit;
        int Agility;

    private:
};

std::ostream &operator<<(std::ostream &os, Character &c);