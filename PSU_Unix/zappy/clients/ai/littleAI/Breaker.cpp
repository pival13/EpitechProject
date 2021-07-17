/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Ubuntu]
** File description:
** Breaker
*/

#include "Breaker.hpp"

Breaker::Breaker(const std::string &teamName)
: Trantorian(teamName)
{
}

Breaker::~Breaker()
{
}

void Breaker::launch()
{
    _constructed = true;
    while (!_isConnect && _isAlive);

    look();
    while (_isAlive)
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void Breaker::actionCallback(FunctionsCode funct, bool result)
{
    if (!_posSynchronized)
        "";//rallyLayer();
    else {
        if (!_world.count(_pos) || result == false)
            look();
        else if (_world[_pos]["player"] > 1 && std::none_of(_otherPlayers.begin(), _otherPlayers.end(), [this](const OtherPlayer &pl) { return pl.pos == _pos; }))
            eject();
        else if (isObjectNear("player", false))
            goToPos(posClosestObject("player", false, false), false);
        else
            move();
    }
}

void Breaker::lookCallback(const std::deque<inv_t> &content)
{
    updateWorld(content);
    actionCallback(Looking, true);
}

void Breaker::messageReceived(Direction /*orig*/, const std::string &_msg)
{
    std::string msg(_msg);
    preParseMessage(msg);
}