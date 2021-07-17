/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019 [WSL: Ubuntu]
** File description:
** Reception
*/

#include "reception/Reception.hpp"

static bool isdouble(char *s)
{
    auto it = std::find_if_not(s, s+strlen(s), isdigit);
    if (*it == '.' && (strlen(it) != 1 || it != s))
        return std::all_of(it+1, it+strlen(it), isdigit);
    else
        return *it == '\0';
}

int main(int n, char **arg)
{
    if (n != 4)
        return 84;
    if (!isdouble(arg[1]) ||
        !std::all_of(arg[2], arg[2]+strlen(arg[2]), isdigit) ||
        !std::all_of(arg[3], arg[3]+strlen(arg[3]), isdigit))
        return 84;

    Plazza::PizzaFactory::setTimeMultiplier(std::stod(arg[1]));
    Plazza::PizzaFactory::addNewPizzaFromFile("./Pizza.plz");

    Plazza::Reception r(std::stoul(arg[2]), std::stoul(arg[3]));
    return r.newDay();
}