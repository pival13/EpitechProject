/*
** EPITECH PROJECT, 2020
** cpp_d16_2019 [WSL: Ubuntu]
** File description:
** Event
*/

#include "Event.hpp"

Event::Event() : _time(), _event() {}
Event::Event(unsigned int time, const std::string &event) : _time(time), _event(event) {}
Event::Event(const Event &other) { *this = other; }
Event::~Event() {}

Event &Event::operator=(const Event &other)
{
    _time = other.getTime();
    _event = other.getEvent();
    return *this;
}

unsigned int Event::getTime() const { return _time; }
const std::string &Event::getEvent() const { return _event; }
void Event::setTime(unsigned int time) { _time = time; }
void Event::setEvent(const std::string &event) { _event = event; }
