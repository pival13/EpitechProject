/*
** EPITECH PROJECT, 2020
** cpp_d10_2019 [WSL: Ubuntu]
** File description:
** AMateria
*/

#include "AMateria.hpp"

AMateria::AMateria(const std::string &type)
: _type(type), _xp(0)
{
}
AMateria::AMateria(const AMateria &materia)
: _type(materia.getType()), _xp(0)
{
}

AMateria::~AMateria()
{
}

AMateria &AMateria::operator=(AMateria &materia)
{
    this->_xp = materia.getXP();
    return *this;
}

const std::string &AMateria::getType() const { return _type; }
unsigned int AMateria::getXP() const { return _xp; }

void AMateria::use(ICharacter &)
{
    _xp += 10;
}