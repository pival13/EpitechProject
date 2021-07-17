/*
** EPITECH PROJECT, 2020
** cpp_d07m_2019 [WSL: Ubuntu]
** File description:
** Federation
*/

#include "Federation.hpp"
#include "Borg.hpp"

/************************************/
/*         Federation::Ship         */
/************************************/

Federation::Ship::Ship(int length, int width, std::string name) : _length(length), _width(width), _name(name), _maxWarp(1), _home(Destination::VULCAN)
{
    _location = _home;
    std::cout << "The independent ship " + name + " just finished its construction.\n";
    std::cout << "It is " << length << " m in length and " << width << " m in width.\n";
}

Federation::Ship::~Ship()
{

}

void Federation::Ship::setupCore(WarpSystem::Core *core)
{
    _core = core;
    std::cout << _name + ": The core is set." << std::endl;
}

void Federation::Ship::checkCore()
{
    std::cout << _name + ": The core is " + (_core->checkReactor()->isStable() ? "stable" : "unstable") + " at the time." << std::endl;
}

WarpSystem::Core *Federation::Ship::getCore()
{
    return _core;
}

bool Federation::Ship::move()
{
    return move(_maxWarp, _home);
}

bool Federation::Ship::move(int warp)
{
    return move(warp, _home);
}

bool Federation::Ship::move(Destination d)
{
    return move(_maxWarp, d);
}

bool Federation::Ship::move(int warp, Destination d)
{
    if (warp > _maxWarp || d == _location)
        return false;
    if (!_core->checkReactor()->isStable())
        return false;
    _location = d;
    return true;
}

/************************************/
/*   Federation::Starfleet::Ship    */
/************************************/

Federation::Starfleet::Ship::Ship(int length, int width, std::string name, short maxWarp, int torpedo) : _length(length),
                                                                                                             _width(width), 
                                                                                                             _name(name), 
                                                                                                             _maxWarp(maxWarp), 
                                                                                                             _home(Destination::EARTH)
{
    _location = _home;
    _shield = 100;
    _photonTorpedo = torpedo;
    std::cout << "The ship USS " + name + " has been finished.\n";
    std::cout << "It is " << length << " m in length and " << width << " m in width.\n";
    std::cout << "It can go to Warp " << maxWarp << "!" << std::endl;
    if (torpedo != 0)
        std::cout << "Weapons are set: " << torpedo << " torpedoes ready." << std::endl;
}

Federation::Starfleet::Ship::Ship() : _length(289),
                                      _width(132), 
                                      _name("Entreprise"), 
                                      _maxWarp(6), 
                                      _home(Destination::EARTH)
{
    Ship(289, 132, "Entreprise", 6, 0);
}

Federation::Starfleet::Ship::~Ship()
{

}

void Federation::Starfleet::Ship::setupCore(WarpSystem::Core *core)
{
    _core = core;
    std::cout << "USS " + _name + ": The core is set." << std::endl;
}

void Federation::Starfleet::Ship::checkCore()
{
    std::cout << "USS " + _name + ": The core is " + (_core->checkReactor()->isStable() ? "stable" : "unstable") + " at the time." << std::endl;
}

void Federation::Starfleet::Ship::promote(Federation::Starfleet::Captain *captain)
{
    _captain = captain;
    std::cout << captain->getName() << ": I'm glad to be the captain of the USS " << _name << "." << std::endl;
}

bool Federation::Starfleet::Ship::move()
{
    return move(_maxWarp, _home);
}

bool Federation::Starfleet::Ship::move(int warp)
{
    return move(warp, _home);
}

bool Federation::Starfleet::Ship::move(Destination d)
{
    return move(_maxWarp, d);
}

bool Federation::Starfleet::Ship::move(int warp, Destination d)
{
    if (warp > _maxWarp || d == _location)
        return false;
    if (!_core->checkReactor()->isStable())
        return false;
    _location = d;
    return true;
}

int Federation::Starfleet::Ship::getShield()
{
    return _shield;
}

void Federation::Starfleet::Ship::setShield(int shield)
{
    _shield = shield;
}

int Federation::Starfleet::Ship::getTorpedo()
{
    return _photonTorpedo;
}

void Federation::Starfleet::Ship::setTorpedo(int torpedo)
{
    _photonTorpedo = torpedo;
}


void Federation::Starfleet::Ship::fire(int torpedoes, Borg::Ship *target)
{
    if (_photonTorpedo > 0) {
        std::cout << _name << ": Firing on target. ";
        if (_photonTorpedo <= torpedoes) {
            std::cout << "0 torpedoes remaining.\n" <<
            _name << ": No more torpedoe to fire, " << _captain->getName() << "!" << std::endl;
            target->setShield(target->getShield() - 50*_photonTorpedo);
            _photonTorpedo = 0;
        } else {
            _photonTorpedo -= torpedoes;
            std::cout << _photonTorpedo << " torpedoes remaining." << std::endl;
            target->setShield(target->getShield() - 50*torpedoes);
        }
    } else {
        std::cout << _name << ": No enough torpedoes to fire, " << _captain->getName() << "!" << std::endl;
    }
}

void Federation::Starfleet::Ship::fire(Borg::Ship *target)
{
    fire(1, target);
}

/************************************/
/*  Federation::Starfleet::Captain  */
/************************************/

Federation::Starfleet::Captain::Captain(std::string name) : _name(name)
{
    
}

Federation::Starfleet::Captain::~Captain()
{

}

std::string Federation::Starfleet::Captain::getName()
{
    return _name;
}

int Federation::Starfleet::Captain::getAge()
{
    return _age;
}

void Federation::Starfleet::Captain::setAge(int age)
{
    _age = age;
}

/************************************/
/*  Federation::Starfleet::Ensign   */
/************************************/

Federation::Starfleet::Ensign::Ensign(std::string name) : _name(name)
{
    std::cout << "Ensign " + name + ", awaiting orders." << std::endl;
}

Federation::Starfleet::Ensign::~Ensign()
{

}
