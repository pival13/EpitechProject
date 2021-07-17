/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** Event
*/

#pragma once

#include "Vector2.hpp"
#include <deque>
#include <map>
#include <SFML/Window.hpp>

struct Event {
    public:
        enum EventType { KeyPressed, KeyReleased, MousePressed, MouseReleased };
        union EventTouch {
            sf::Keyboard::Key key;
            enum { LeftClick, RightClick, Wheel } mouseButton;
        };

        std::deque<std::pair<EventType, EventTouch>> events;

        Vector2 mousePosition;
        bool mouseRightIsPressed;
        bool mouseLeftIsPressed;
        bool mouseWheelIsPressed;
        bool ctrlIsPressed;
        bool altIsPressed;
        bool shiftIsPressed;
};
