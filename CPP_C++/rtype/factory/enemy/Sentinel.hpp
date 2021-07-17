/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** Sentinel
*/

#pragma once

#include "Enemy.hpp"
#include "DLLoader.hpp"

class Sentinel : public Enemy {
    public:
        Sentinel();
        ~Sentinel();

    protected:
    private:
};

DllExport Enemy *createInstance();