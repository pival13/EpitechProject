/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** RTypeExtern
*/

#include "RType.hpp"

const size_t RType::maxPlayer = 4;
const double RType::border = 100;
const double RType::mapWidth = 1500;
const double RType::mapHeight = 1000;

std::list<RTypeObject *> RType::getPlayers() const
{
    std::list<RTypeObject *> obj;
    for (const auto &p : players)
        if (elements.count(p.second))
            obj.push_back(elements.at(p.second).get());
    return obj;
}

size_t RType::objectToUuid(const RTypeObject *obj)
{
    for (const auto &p : elements)
        if (p.second.get() == obj)
            return p.first;
    return size_t(-1);
}

void RType::addEvents(RTypeEvents::EventType type, const RTypeObject *obj)
{
    RTypeEvents ev = {};
    ev.type = type;
    if (type != RTypeEvents::EventType::GameTime && type != RTypeEvents::PlayerScore)
        ev.objectUuid = objectToUuid(obj);
    events.push_back(ev);
}