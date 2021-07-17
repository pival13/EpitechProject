/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** DestroyableObstacle
*/

#pragma once

#include "Obstacle.hpp"
#include "DLLoader.hpp"

class DestroyableObstacle : public Obstacle {
    public:
        DestroyableObstacle();
        ~DestroyableObstacle();

    protected:
    private:
};

DllExport Obstacle *createInstance();