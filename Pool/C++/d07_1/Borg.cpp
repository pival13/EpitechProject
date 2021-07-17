/*
** EPITECH PROJECT, 2020
** cpp_d07m_2019 [WSL: Ubuntu]
** File description:
** Borg
*/

#include "Borg.hpp"
#include "Federation.hpp"

Borg::Ship::Ship(int weaponFrequency, short repair) : _side(300), _maxWarp(9), _home(Destination::UNICOMPLEX)
{
    _location = _home;
    _shield = 100;
    _weaponFrequency = weaponFrequency;
    _repair = repair;
    std::cout << "We are the Borgs. Lower your shields and surrender yourselves unconditionally.\n" <<
                 "Your biological characteristics and technologies will be assimilated.\n" <<
                 "Resistance is futile." << std::endl;

}

Borg::Ship::~Ship()
{
}

void Borg::Ship::setupCore(WarpSystem::Core *core)
{
    _core = core;
}

void Borg::Ship::checkCore()
{
    if (_core->checkReactor()->isStable())
        std::cout << "Everything is in order." << std::endl;
    else
        std::cout << "Critical failure imminent." << std::endl;
}

int Borg::Ship::getShield()
{
    return _shield;
}

void Borg::Ship::setShield(int shield)
{
    _shield = shield;
}

int Borg::Ship::getWeaponFrequency()
{
    return _weaponFrequency;
}

void Borg::Ship::setWeaponFrequency(int frequency)
{
    _weaponFrequency = frequency;
}

short Borg::Ship::getRepair()
{
    return _repair;
}

void Borg::Ship::setRepair(short repair)
{
    _repair = repair;
}


bool Borg::Ship::move()
{
    return move(_maxWarp, _home);
}

bool Borg::Ship::move(int warp)
{
    return move(warp, _home);
}

bool Borg::Ship::move(Destination d)
{
    return move(_maxWarp, d);
}

bool Borg::Ship::move(int warp, Destination d)
{
    if (warp > _maxWarp || d == _location)
        return false;
    if (!_core->checkReactor()->isStable())
        return false;
    _location = d;
    return true;
}

void Borg::Ship::fire(Federation::Starfleet::Ship *target)
{
    target->setShield(target->getShield()-_weaponFrequency);
    std::cout << "Firing on target with " << _weaponFrequency << "GW frequency." << std::endl;
}

void Borg::Ship::fire(Federation::Ship *target)
{
    target->getCore()->checkReactor()->setStability(false);
    std::cout << "Firing on target with " << _weaponFrequency << "GW frequency." << std::endl;
}

void Borg::Ship::repair()
{
    if (_repair > 0) {
        _shield = 100;
        _repair--;
        std::cout << "Begin shield re-initialisation... Done. Awaiting further instructions." << std::endl;
    } else
        std::cout << "Energy cells depleted, shield weakening." << std::endl;
}
