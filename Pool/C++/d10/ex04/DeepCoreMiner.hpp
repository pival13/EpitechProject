/*
** EPITECH PROJECT, 2020
** cpp_d10_2019 [WSL: Ubuntu]
** File description:
** DeepCoreMiner
*/

#pragma once

#include "IMiningLaser.hpp"
#include "IAsteroid.hpp"
#include <iostream>

class DeepCoreMiner : public IMiningLaser {
    public:
        DeepCoreMiner();
        ~DeepCoreMiner();

        void mine(IAsteroid *);

    protected:
    private:
};
