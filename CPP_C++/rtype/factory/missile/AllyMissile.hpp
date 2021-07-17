/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** AllyMissile
*/

#pragma once

#include "Missile.hpp"
#include "DLLoader.hpp"

class AllyMissile : public Missile {
    public:
        AllyMissile();
        ~AllyMissile();

    protected:
    private:
};

DllExport Missile *createInstance();