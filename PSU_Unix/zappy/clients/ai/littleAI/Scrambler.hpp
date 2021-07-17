/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Ubuntu]
** File description:
** Scrambler
*/

#pragma once

#include "../Trantorian.hpp"

class Scrambler : public Trantorian {
    public:
        Scrambler(const std::string &teamName);
        ~Scrambler();

        void launch();

    protected:
        void actionCallback(FunctionsCode /*funct*/, bool /*result*/) {}
        void lookCallback(const std::deque<inv_t> &/*content*/) {}
        void inventoryCallback(const inv_t &/*inventory*/) {}
        void messageReceived(Direction orig, const std::string &msg);
        void beenEject(Direction /*orig*/) {}
        void isDead() {}
        void inIncantation() {}
        void remainingPlace(size_t /*remainingPlaces*/) {}
};
