/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Ubuntu]
** File description:
** Scrambler
*/

#include "Scrambler.hpp"

Scrambler::Scrambler(const std::string &teamName)
: Trantorian(teamName)
{
}

Scrambler::~Scrambler()
{
}

void Scrambler::launch()
{
    while (_isAlive)
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void Scrambler::messageReceived(Direction /*orig*/, const std::string &_msg)
{
    std::string msg(_msg);
    if (preParseMessage(msg))
        return;

    std::smatch m;
    std::string s;
    while (std::regex_search(msg, m, std::regex("\\d+"))) {
        s += m.prefix().str() + std::to_string(std::stoul(m[0])+1);
        msg = m.suffix();
    }
    s += msg;
    talk(_msg);
    talk(s);
}