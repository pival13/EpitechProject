/*
** EPITECH PROJECT, 2020
** cpp_rush3_2019 [WSL: Ubuntu]
** File description:
** AModuleOneTime
*/

#include "AModuleOneTime.hpp"

AModuleOneTime::AModuleOneTime(const std::string &name)
: _name(name), _isActive(true)
{
}

AModuleOneTime::~AModuleOneTime()
{
}

const std::string &AModuleOneTime::getName() const { return _name; }
bool AModuleOneTime::getStatus() const { return _isActive; }
bool AModuleOneTime::isDrawable() const { return false; }
oneTimeInfo AModuleOneTime::getOneInfo() const { return _info; }
sixtyTimeInfo AModuleOneTime::getSixtyInfo() const { return (sixtyTimeInfo()); }
void AModuleOneTime::setStatus(bool status) { _isActive = status; }