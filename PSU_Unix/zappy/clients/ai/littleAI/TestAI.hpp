/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Ubuntu]
** File description:
** TestAI
*/

#pragma once

#include "../AI.hpp"
#include "Json/Json.hpp"
#include <regex>
#include <unordered_map>
#include <array>

class TestAI : public AI {
    public:
        TestAI(const std::string &teamName);
        ~TestAI();

        void launch();

    protected:
        void actionCallback(FunctionsCode funct, bool result);
        void lookCallback(const std::deque<inv_t> &content);
        void inventoryCallback(const inv_t &inventory);
        void messageReceived(Direction orig, const std::string &msg);
        void beenEject(Direction orig);
        void isDead();
        void inIncantation();
        void remainingPlace(size_t remainingPlaces);
    
    private:
        std::unordered_map<std::string, void (AI::*)()> funct = {
            {"Forward", &AI::move},
            {"Right", &AI::turnRight},
            {"Left", &AI::turnLeft},
            {"Look", &AI::look},
            {"Inventory", &AI::getInventory},
            {"Connect_nbr", &AI::getRemainingPlace},
            {"Fork", &AI::layEgg},
            {"Eject", &AI::eject},
            {"Incantation", &AI::incantate}
        };
        std::unordered_map<std::string, void (AI::*)(const std::string &)> functString = {
            {"Broadcast @@@", &AI::talk},
            {"Take @@@", &AI::take},
            {"Set @@@", &AI::drop}
        };
};
