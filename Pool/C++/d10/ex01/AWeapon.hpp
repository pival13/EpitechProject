/*
** EPITECH PROJECT, 2020
** cpp_d10_2019 [WSL: Ubuntu]
** File description:
** AWeapon
*/

#pragma once

#include <iostream>

class AWeapon {
    public:
        AWeapon(const std::string &name, int apcost, int damage);
        virtual ~AWeapon();

        const std::string getName() const;
        int getAPCost() const;
        int getDamage() const;

        virtual void attack() const = 0;

    protected:
        const std::string _Name;
        int _Damage;
        int _APCost;

    private:
};
