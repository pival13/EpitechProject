/*
** EPITECH PROJECT, 2020
** cpp_d10_2019 [WSL: Ubuntu]
** File description:
** Character
*/

#include "Character.hpp"

Character::Character(const std::string &name)
: _name(name), _materia()
{
}

Character::Character(const Character &c)
: _name(c.getName())
{
    *this = c;
}

Character::~Character()
{
    for (size_t i = 0; i != _materia.size(); i++)
        if (_materia[i])
            delete _materia[i];
}

Character &Character::operator=(const Character &c)
{
    for (size_t i = 0; i != _materia.size(); i++) {
        if (_materia[i])
            delete _materia[i];
        if (c.getMateria(i))
            _materia[i] = c.getMateria(i)->clone();
        else
            _materia[i] = nullptr;
    }
    return *this;
}

const std::string &Character::getName() const { return _name; }
AMateria *Character::getMateria(int i) const { return _materia[i]; }

void Character::equip(AMateria* m)
{
    if (m == nullptr)
        return;
    for (size_t i = 0; i != _materia.size(); i++)
        if (_materia[i] == nullptr) {
            _materia[i] = m->clone();
            return;
        }
}

void Character::unequip(int idx)
{
    if (idx > (int)_materia.size()-1 || idx < 0 || _materia[idx] == nullptr)
        return;
    for (int i = idx; i != (int)_materia.size()-1; i++)
        _materia[i] = _materia[i+1];
    _materia[_materia.size()-1] = nullptr;
}

void Character::use(int idx, ICharacter& target)
{
    if (idx > (int)_materia.size()-1 || idx < 0 || _materia[idx] == nullptr)
        return;
    _materia[idx]->use(target);
}
