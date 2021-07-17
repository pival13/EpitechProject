/*
** EPITECH PROJECT, 2020
** cpp_rush3_2019
** File description:
** GraphicMenu
*/

#ifndef GRAPHICMENU_HPP_
#define GRAPHICMENU_HPP_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Graphic.hpp"

class GraphicMenu {
    public:
        GraphicMenu(std::map<std::string, bool> &settings, sf::Vector2i);
        ~GraphicMenu();
        void menu();
        void getEvent();
        void draw();

    private:
        sf::Event _evt;
        sf::VideoMode _vm;
        sf::RenderWindow _rwindow;
        std::map<std::string, bool> _settings;
        int _size_map;
        sf::Font _font;
        std::vector<sf::Text> _txt;
        std::vector<sf::RectangleShape> _buttons;
};

#endif /* !GRAPHICMENU_HPP_ */