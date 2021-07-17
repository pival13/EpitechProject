/*
** EPITECH PROJECT, 2020
** cpp_rush3_2019 [WSL: Ubuntu]
** File description:
** ModuleCPU
*/

#pragma once

#include "AModuleSixtyTime.hpp"

class ModuleCPU : public AModuleSixtyTime {
    public:
        ModuleCPU();
        ~ModuleCPU();

        void update();

    private:
        void initialUpdate();
};
