/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** Soldier
*/

#pragma once

#include "Enemy.hpp"
#include "DLLoader.hpp"

class Soldier : public Enemy {
    public:
        Soldier();
        ~Soldier();

        void update(RType &rt, const std::list<Collider *> &colliders, RTypeDestroy destroyer, RTypeCreate creater);
        
    private:
        Vector3 getCloserEnemyAngle(RType &rt);

    protected:
    private:
        std::chrono::system_clock::time_point lastShoot;
};

DllExport Enemy *createInstance();