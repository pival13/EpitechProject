/*
** EPITECH PROJECT, 2020
** cpp_d10_2019 [WSL: Ubuntu]
** File description:
** AWeapon
*/

#include "AWeapon.hpp"

AWeapon::AWeapon(const std::string &name, int apcost, int damage)
: _Name(name), _Damage(damage), _APCost(apcost)
{
}

AWeapon::~AWeapon()
{
}

const std::string AWeapon::getName() const { return _Name; }
int AWeapon::getAPCost() const { return _APCost; }
int AWeapon::getDamage() const { return _Damage; }