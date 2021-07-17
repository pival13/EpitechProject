/*
** EPITECH PROJECT, 2020
** cpp_d09_2019 [WSL: Ubuntu]
** File description:
** Priest
*/

#pragma once

#include "Mage.hpp"

class Priest : public Mage {
    public:
        Priest(const std::string &name, int level);
        ~Priest();

        int CloseAttack();
        int RangeAttack();
        void Heal();
        void RestorePower();

    protected:

    private:
};
