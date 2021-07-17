/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** Windows
*/

#pragma once

#include "GameObject.hpp"
#include "Drawable.hpp"
#include "Event.hpp"

#include <SFML/Window.hpp>

class Windows : virtual public GameObject {
    public:
        Windows(const std::string &title, GameObject *parent=nullptr);
        ~Windows();

        bool isOpen() const { return _isOpen; }

        void setTitle(const std::string &title) { _window.setTitle(title); }
        void setSize(const Vector2 &size) { _window.setSize({uint32_t(size.x), uint32_t(size.y)}); }
        void setIcon(const std::string &file);
        void draw(Drawable &obj);
        void display();
        Event getEvents();

    private:
        sf::RenderWindow _window;
        bool _isOpen;
};
