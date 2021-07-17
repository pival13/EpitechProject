/*
** EPITECH PROJECT, 2020
** cpp_d10_2019 [WSL: Ubuntu]
** File description:
** Peon
*/

#include "Peon.hpp"

Peon::Peon(const std::string &name)
: Victim(name)
{
    std::cout << "Zog zog." << std::endl;
}

Peon::~Peon()
{
    std::cout << "Bleuark..." << std::endl;
}

void Peon::getPolymorphed() const
{
    std::cout << _name << " has been turned into a pink pony!" << std::endl;
}