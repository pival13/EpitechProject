/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** Game
*/

#pragma once

#include <cstdint>
#include <vector>

class Game {
    public:
        virtual ~Game() = default;

        virtual void receiveInputs(const std::string &id, const std::vector<uint8_t> &data) = 0;
        virtual std::vector<uint8_t> exportOutputs() const = 0;

        virtual bool addPlayer(const std::string &playerId) = 0;
};
