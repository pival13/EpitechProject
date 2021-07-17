/*
** EPITECH PROJECT, 2020
** cpp_d10_2019 [WSL: Ubuntu]
** File description:
** AEnemy
*/

#pragma once

#include <iostream>

class AEnemy {
    public:
        AEnemy(int hp, const std::string &type);
        virtual ~AEnemy();

        const std::string getType() const;
        int getHP() const;

        virtual void takeDamage(int damage);

    protected:
        const std::string _type;
        int _hp;

    private:
};
