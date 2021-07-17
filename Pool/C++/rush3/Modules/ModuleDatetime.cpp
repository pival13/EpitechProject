/*
** EPITECH PROJECT, 2020
** cpp_rush3_2019 [WSL: Ubuntu]
** File description:
** ModuleDatetime
*/

#include "ModuleDatetime.hpp"

ModuleDatetime::ModuleDatetime()
: AModuleOneTime("Date & Time")
{
    update();
}

ModuleDatetime::~ModuleDatetime()
{
}

void ModuleDatetime::update()
{
    char buff[100];

    long now = std::chrono::system_clock::now().time_since_epoch().count() / 1000000000;

    strftime(buff, 100, "%a %d %b %Y", localtime(&now));
    _info["Date"] = buff;

    strftime(buff, 100, "%X", localtime(&now));
    _info["Time"] = buff;
}