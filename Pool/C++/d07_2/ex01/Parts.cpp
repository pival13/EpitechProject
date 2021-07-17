/*
** EPITECH PROJECT, 2020
** cpp_d07a_2019 [WSL: Ubuntu]
** File description:
** Parts
*/

#include "Parts.hpp"

Parts::Parts(const std::string &part, const std::string &serial, bool functional) 
: _name(serial), _part(part), _functional(functional)
{
}

Parts::~Parts()
{
}

bool Parts::isFunctional() const
{
    return _functional;
}

std::string Parts::serial() const
{
    return _name;
}

void Parts::informations() const
{
    std::cout << "\t[Parts] " << _part << " " << _name << " status : " << (_functional ? "OK" : "KO") << std::endl;
}

Arms::Arms(const std::string &serial, bool functional) : Parts("Arms", serial, functional)
{
}

Arms::~Arms()
{
}

Legs::Legs(const std::string &serial, bool functional) : Parts("Legs", serial, functional)
{
}

Legs::~Legs()
{
}

Head::Head(const std::string &serial, bool functional) : Parts("Head", serial, functional)
{
}

Head::~Head()
{
}
