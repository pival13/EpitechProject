/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** SmallOstacle
*/

#pragma once

#include "Obstacle.hpp"
#include "DLLoader.hpp"

class SmallOstacle : public Obstacle {
    public:
        SmallOstacle();
        ~SmallOstacle();

    protected:
    private:
};

DllExport Obstacle *createInstance();