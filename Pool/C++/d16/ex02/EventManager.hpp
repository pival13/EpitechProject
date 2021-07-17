/*
** EPITECH PROJECT, 2020
** cpp_d16_2019 [WSL: Ubuntu]
** File description:
** EventManager
*/

#pragma once

#include "Event.hpp"
#include <list>

class EventManager {
	public:
		EventManager();
        EventManager(const EventManager &other);
		~EventManager();

        EventManager &operator=(const EventManager &other);

        const std::list<Event> &getEvents() const;
        unsigned int getTime() const;

        void addEvent(const Event &e);
        void removeEventsAt(unsigned int time);
        void dumpEvents() const;
        void dumpEventAt(unsigned int time) const;
        void addTime(unsigned int time);
        void addEventList(std::list<Event> &event);

	protected:
	private:
        unsigned int _time;
        std::list<Event> _event;
};
