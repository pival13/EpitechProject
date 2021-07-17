/*
** EPITECH PROJECT, 2020
** cpp_rush3_2019 [WSL: Ubuntu]
** File description:
** ModuleName
*/

#include "ModuleName.hpp"

ModuleName::ModuleName()
: AModuleOneTime("Name")
{
    update();
}

ModuleName::~ModuleName()
{
}

void ModuleName::update()
{
    if (getenv("USER"))
        _info["Username"] = getenv("USER");
    else if (getenv("USERNAME"))
        _info["Username"] = getenv("USERNAME");
    else if (getenv("LOGNAME"))
        _info["Username"] = getenv("LOGNAME");
    else
        _info["Username"] = "[no username]";

    std::ifstream f("/proc/sys/kernel/hostname");
    if (!f.is_open())
        _info["Hostname"] = "[no hostname]";
    else
        std::getline(f, _info["Hostname"]);
    f.close();
}