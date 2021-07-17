/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019 [WSL: Ubuntu]
** File description:
** my_except
*/

#include "my_except.hpp"

nts::my_except::my_except(const std::string &str)
{
    this->str = str;
}

nts::my_except::~my_except()
{
}

const char *nts::my_except::what() const throw()
{
    return str.c_str();
}