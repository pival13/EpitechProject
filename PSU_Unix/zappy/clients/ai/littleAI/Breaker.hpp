/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Ubuntu]
** File description:
** Breaker
*/

#pragma once

#include "../Trantorian.hpp"

class Breaker : public Trantorian {
    public:
        Breaker(const std::string &teamName);
        ~Breaker();

        void launch();

    protected:
        void actionCallback(FunctionsCode /*funct*/, bool /*result*/);
        void lookCallback(const std::deque<inv_t> &/*content*/);
        void messageReceived(Direction orig, const std::string &msg);

        void inventoryCallback(const inv_t &/*inventory*/) {}
        void isDead() {}
        void inIncantation() {}
        void remainingPlace(size_t /*remainingPlaces*/) {}
};
