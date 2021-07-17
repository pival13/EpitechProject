/*
** EPITECH PROJECT, 2020
** cpp_d16_2019 [WSL: Ubuntu]
** File description:
** Event
*/

#pragma once

#include <iostream>

class Event {
	public:
		Event();
		Event(unsigned int time, const std::string &event);
        Event(const Event &other);
		~Event();

        Event &operator=(const Event &other);

        unsigned int getTime() const;
        const std::string &getEvent() const;
        void setTime(unsigned int time);
        void setEvent(const std::string &event);

	protected:
	private:
        unsigned int _time;
        std::string _event;
};
