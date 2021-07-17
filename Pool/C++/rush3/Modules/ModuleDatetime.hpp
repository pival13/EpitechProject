/*
** EPITECH PROJECT, 2020
** cpp_rush3_2019 [WSL: Ubuntu]
** File description:
** ModuleDatetime
*/

#pragma once

#include "AModuleOneTime.hpp"
#include <chrono>
#include <ctime>

class ModuleDatetime : public AModuleOneTime {
    public:
        ModuleDatetime();
        ~ModuleDatetime();

        void update();
};
