/*
** EPITECH PROJECT, 2020
** cpp_rush3_2019 [WSL: Ubuntu]
** File description:
** IMonitorDisplay
*/

#pragma once

#include "IMonitorModule.hpp"

class IMonitorDisplay {
    public:
        virtual ~IMonitorDisplay() {};

        virtual void getEvents() = 0;
        virtual void updateModules() = 0;
        virtual void drawModules() = 0;
        virtual bool isEnd() const = 0;
};
