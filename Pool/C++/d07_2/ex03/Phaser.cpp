/*
** EPITECH PROJECT, 2020
** cpp_d07a_2019 [WSL: Ubuntu]
** File description:
** Phaser
*/

#include "Phaser.hpp"
#include "Sounds.hpp"

const int Phaser::Empty = 0;

Phaser::Phaser(int maxAmmo, AmmoType type)
: _maxAmmo(maxAmmo), _type(type)
{
    Sounds s;
    sounds[REGULAR] = s.Regular;
    sounds[PLASMA] = s.Plasma;
    sounds[ROCKET] = s.Rocket;
    for (int i = 0; i != maxAmmo; i++)
        _ammo.push(type);
}

Phaser::~Phaser()
{
}

void Phaser::fire()
{
    if (_ammo.empty()) {
        std::cout << "Clip empty, please reload\n";
    } else {
        std::cout << sounds[_ammo.front()] << std::endl;
        _ammo.pop();
    }
}

void Phaser::ejectClip()
{
    while (!_ammo.empty())
        _ammo.pop();
}

void Phaser::changeType(AmmoType newType)
{
    std::cout << "Switching ammo to type: ";
    if (newType == AmmoType::REGULAR)
        std::cout << "regular\n";
    else if (newType == AmmoType::PLASMA)
        std::cout << "plasma\n";
    else if (newType == AmmoType::ROCKET)
        std::cout << "rocket\n";
    _type = newType;        
}

void Phaser::reload()
{
    std::cout << "Reloading...\n";
    while (_maxAmmo > _ammo.size())
        _ammo.push(_type);
}

void Phaser::addAmmo(AmmoType type)
{
    if (_ammo.size() != _maxAmmo)
        _ammo.push(type);
    else
        std::cout << "Clip full\n";
}

int Phaser::getCurrentAmmos() const
{
    return _ammo.size();
}