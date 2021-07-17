/*
** EPITECH PROJECT, 2020
** cpp_d13_2019 [WSL: Ubuntu]
** File description:
** Woody
*/

#include "Woody.hpp"

Woody::Woody(const std::string &name, const std::string &file)
: Toy(Toy::WOODY, name, file)
{
}

Woody::~Woody()
{
}

void Woody::speak(const std::string &str) const
{
    std::cout << "WOODY: ";
    Toy::speak(str);
}