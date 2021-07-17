/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Ubuntu]
** File description:
** TestAI
*/

#include "TestAI.hpp"

TestAI::TestAI(const std::string &team) : AI(team) {}
TestAI::~TestAI() {}

void TestAI::launch()
{
    _constructed = true;
    Json json = getSettingsAI();
    std::string s, s2;
    for (std::getline(std::cin, s); !std::cin.eof() && _isAlive; std::getline(std::cin, s)) {
        s2 = std::regex_replace(s, std::regex(" .*$"), " @@@");
        if (funct.count(s))
            (this->*funct[s])();
        else if (functString.count(s2))
            (this->*functString[s2])(std::regex_replace(s, std::regex("^[^ ]+ "), ""));
        else if (s == "/help" || s == "/list" || s == "/h" || s == "/l") {
            std::cout << "List of possible action (@@@ can be replace by any string):" << std::endl;
            for (auto &it : funct)
                std::cout << "  * " << it.first << std::endl;
            for (auto &it : functString)
                std::cout << "  * " << it.first << std::endl;
        } else if (s == "/elevate" || s == "/incant") {
            std::cout << "Current level: " << _currentLevel << ", next level requirement:" << std::endl;
            for (auto &s : json["elevationPath"][_currentLevel-1].keys())
                std::cout << "  * " << s << ": " << json["elevationPath"][_currentLevel-1][s] << std::endl;
        } else
            std::cerr << s << " is not a valid command" << std::endl;
    }
}

void TestAI::actionCallback(FunctionsCode, bool result) { std::cout << (result ? "Success" : "Failure") << std::endl; }
void TestAI::lookCallback(const std::deque<inv_t> &content) { for (const inv_t &inv : content) { std::cout << "Player: " << inv.at("player") << ", Food: " << inv.at("food") << ", Linemate: " << inv.at("linemate") << ", Deraumere: " << inv.at("deraumere") << ", Sibur: " << inv.at("sibur") << ", Mendiane: " << inv.at("mendiane") << ", Phiras: " << inv.at("phiras") << ", Thystame: " << inv.at("thystame") << std::endl; } }
void TestAI::inventoryCallback(const inv_t &inventory) { std::cout << "Food: " << inventory.at("food") << ", Linemate: " << inventory.at("linemate") << ", Deraumere: " << inventory.at("deraumere") << ", Sibur: " << inventory.at("sibur") << ", Mendiane: " << inventory.at("mendiane") << ", Phiras: " << inventory.at("phiras") << ", Thystame: " << inventory.at("thystame") << std::endl; }
void TestAI::messageReceived(Direction orig, const std::string &msg) { std::cout << "\"" << msg << "\" from " << (orig == Self? "here": (orig == Front? "ahead": (orig == FrontLeft? "front left": (orig == Left? "left": (orig == BackLeft? "back left": (orig == Back? "behind": (orig == BackRight? "back right": (orig == Right? "right": "front right")))))))) << std::endl; }
void TestAI::beenEject(Direction orig) { std::cout << "Pushed from " << (orig == Self? "here": (orig == Front? "ahead": (orig == FrontLeft? "front left": (orig == Left? "left": (orig == BackLeft? "back left": (orig == Back? "behind": (orig == BackRight? "back right": (orig == Right? "right": "front right")))))))) << std::endl; }
void TestAI::isDead() { std::cout << "It's the end" << std::endl; }
void TestAI::inIncantation() { std::cout << "Begin incantate" << std::endl; }
void TestAI::remainingPlace(size_t remainingPlaces) { std::cout << remainingPlaces << " places remaining in the team" << std::endl; }