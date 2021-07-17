/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** RTPlayer
*/

#pragma once

#include "Player.hpp"
#include "DLLoader.hpp"

class RTPlayer : public Player {
    public:
        RTPlayer();
        ~RTPlayer();

        size_t beenCollided();

        void update(RType &rt, const std::list<Collider *> &colliders, RTypeDestroy destroyer, RTypeCreate creater);
        void shoot();

    protected:
    private:
        bool _shoot = false;
        std::chrono::system_clock::time_point lastShoot;
        std::chrono::milliseconds shootCadence;
};

DllExport Player *createInstance();