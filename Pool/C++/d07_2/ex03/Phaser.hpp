/*
** EPITECH PROJECT, 2020
** cpp_d07a_2019 [WSL: Ubuntu]
** File description:
** Phaser
*/

#pragma once

#include <iostream>
#include <queue>

class Phaser {
    public:
        enum AmmoType {
            REGULAR,
            PLASMA,
            ROCKET
        };

        Phaser(int maxAmmo=20, AmmoType type=REGULAR);
        ~Phaser();

        void fire();
        void ejectClip();
        void changeType(AmmoType newType);
        void reload();
        void addAmmo(AmmoType type);

        int getCurrentAmmos() const;
    private:
        static const int Empty;// = 0;
        AmmoType _type;
        std::queue<AmmoType> _ammo;
        const int _maxAmmo;
        std::string sounds[3];
};