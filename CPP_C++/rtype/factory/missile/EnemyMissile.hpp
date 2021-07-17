/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** EnemyMissile
*/

#pragma once

#include "Missile.hpp"
#include "DLLoader.hpp"

class EnemyMissile : public Missile {
    public:
        EnemyMissile();
        ~EnemyMissile();

    protected:
    private:
};

DllExport Missile *createInstance();