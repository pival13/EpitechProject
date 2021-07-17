/*
** EPITECH PROJECT, 2020
** cpp_d10_2019 [WSL: Ubuntu]
** File description:
** Character
*/

#include "Character.hpp"

Character::Character(const std::string &name)
: _name(name), _AP(40), _weapon(nullptr)
{
}

Character::~Character()
{
}

const std::string Character::getName() const { return _name; }
int Character::getAP() const { return _AP; }
AWeapon *Character::getWeapon() const { return _weapon; }

void Character::recoverAP()
{
    _AP += 10;
    if (_AP > 40)
        _AP = 40;
}

void Character::equip(AWeapon *weapon)
{
    if (weapon == nullptr)
        return;
    _weapon = weapon;
}

void Character::attack(AEnemy *enemy)
{
    if (enemy == nullptr || _weapon == nullptr || _weapon->getAPCost() > _AP)
        return;
    _AP -= _weapon->getAPCost();
    std::cout << _name << " attacks " << enemy->getType() << " with a " << _weapon->getName() << std::endl;
    _weapon->attack();
    enemy->takeDamage(_weapon->getDamage());
    if (enemy->getHP() <= 0)
        delete enemy;
}

std::ostream &operator<<(std::ostream &os, Character const &c)
{
    os << c.getName() << " has " << c.getAP() << " AP and ";
    if (c.getWeapon() == nullptr)
        os << "is unarmed" << std::endl;
    else
        os << "wields a " << c.getWeapon()->getName() << std::endl;
    return os;
}