/*
** EPITECH PROJECT, 2020
** cpp_d16_2019 [WSL: Ubuntu]
** File description:
** EventManager
*/

#include "EventManager.hpp"

EventManager::EventManager() : _time(0), _event() {}

EventManager::EventManager(const EventManager &other) { *this = other; }

EventManager::~EventManager() {}

EventManager &EventManager::operator=(const EventManager &other)
{
    _event.clear();
    for (Event e : other.getEvents())
        _event.push_back(e);
    _time = other.getTime();
    return *this;
}

const std::list<Event> &EventManager::getEvents() const { return _event; }
unsigned int EventManager::getTime() const { return _time; }

void EventManager::addEvent(const Event &e)
{
    if (e.getTime() <= _time)
        return;
    for (auto it = _event.begin(); it != _event.end(); ++it)
        if (it->getTime() > e.getTime()) {
            _event.insert(it, e);
            return;
        }
    _event.push_back(e);
}

void EventManager::removeEventsAt(unsigned int time)
{
    _event.remove_if([time](const Event &e) { return (e.getTime() == time); });
}

void EventManager::dumpEvents() const
{
    for (Event e : _event)
        std::cout << e.getTime() << ": " << e.getEvent() << std::endl;
}

void EventManager::dumpEventAt(unsigned int time) const
{
    for (Event e : _event)
        if (e.getTime() == time)
            std::cout << e.getTime() << ": " << e.getEvent() << std::endl;
}

void EventManager::addTime(unsigned int time)
{
    _time += time;
    while (_event.size() > 0 && _event.front().getTime() <= _time) {
        std::cout << _event.front().getEvent() << std::endl;
        _event.pop_front();
    }
}

void EventManager::addEventList(std::list<Event> &event)
{
    for (Event e : event)
        addEvent(e);
}