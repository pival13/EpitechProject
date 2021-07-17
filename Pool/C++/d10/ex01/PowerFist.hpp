/*
** EPITECH PROJECT, 2020
** cpp_d10_2019 [WSL: Ubuntu]
** File description:
** PowerFist
*/

#pragma once

#include "AWeapon.hpp"

class PowerFist : public AWeapon {
    public:
        PowerFist();
        ~PowerFist();

        void attack() const override;

    protected:
    private:
};
