/*
** EPITECH PROJECT, 2020
** cpp_d10_2019 [WSL: Ubuntu]
** File description:
** Character
*/

#pragma once

#include "AWeapon.hpp"
#include "AEnemy.hpp"

class Character {
    public:
        Character(const std::string &name);
        ~Character();

        const std::string getName() const;
        int getAP() const;
        AWeapon *getWeapon() const;

        void recoverAP();
        void equip(AWeapon *weapon);
        void attack(AEnemy *enemy);

    protected:
        const std::string _name;
        int _AP;
        AWeapon *_weapon;
    private:
};

std::ostream &operator<<(std::ostream &os, Character const &);