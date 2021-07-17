/*
** EPITECH PROJECT, 2020
** cpp_d07a_2019 [WSL: Ubuntu]
** File description:
** Skat
*/

#include "Skat.hpp"

Skat::Skat(const std::string &name, int stimPaks) : _name(name), _stimPacks(stimPaks)
{
}

Skat::~Skat()
{
}

int &Skat::stimPaks()
{
    return _stimPacks;
}

const std::string &Skat::name()
{
    return _name;
}

void Skat::shareStimPaks(int number, int &stock)
{
    if (number > _stimPacks) {
        std::cout << "Don't be greedy\n";
        return;
    }
    std::cout << "Keep the change.\n";
    _stimPacks -= number;
    stock += number;
}

void Skat::addStimPaks(unsigned int number)
{
    if (number == 0)
        std::cout << "Hey boya, did you forget something?\n";
    _stimPacks += number;
}

void Skat::useStimPaks()
{
    if (_stimPacks > 0) {
        std::cout << "Time to kick some ass and chew bubble gum.\n";
        _stimPacks--;
    } else {
        std::cout << "Mediiiiiic\n";
    }
}

void Skat::status() const
{
    std::cout << "Soldier " + _name + " reporting " << _stimPacks << " stimpaks remaining sir!" << std::endl;
}