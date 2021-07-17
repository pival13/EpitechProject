/*
** EPITECH PROJECT, 2020
** cpp_d10_2019 [WSL: Ubuntu]
** File description:
** Squad
*/

#include "Squad.hpp"

Squad::Squad()
{
}

Squad::Squad(const Squad &s)
{
    *this = s;
}

Squad::~Squad()
{
    while (_units.size() > 0) {
        delete _units[0];
        _units.erase(_units.begin());
    }
}

Squad &Squad::operator=(const Squad &s)
{
    while (_units.size() > 0) {
        delete _units[0];
        _units.erase(_units.begin());
    }
    for (int i = 0; i != s.getCount(); i++)
        _units.push_back(s.getUnit(i)->clone());
    return *this;
}

int Squad::getCount() const { return _units.size(); }

ISpaceMarine *Squad::getUnit(int i) const
{
    if (i < 0 || i >= (int)_units.size())
        return nullptr;
    return _units.at(i);
}

ISpaceMarine *Squad::getUnit(int i)
{
    if (i < 0 || i >= (int)_units.size())
        return nullptr;
    return _units[i];
}

int Squad::push(ISpaceMarine *space)
{
    if (!space)
        return _units.size();
    for (size_t i = 0; i != _units.size(); i++)
        if (_units[i] == space)
            return _units.size();
    _units.push_back(space->clone());
    return _units.size();
}