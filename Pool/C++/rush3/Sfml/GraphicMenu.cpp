/*
** EPITECH PROJECT, 2020
** cpp_rush3_2019
** File description:
** GraphicMenu
*/

#include "GraphicMenu.hpp"

GraphicMenu::GraphicMenu(std::map<std::string, bool> &settings, sf::Vector2i posWin)
: _vm(150, 100) ,_rwindow(_vm, "", sf::Style::None), _settings(settings)
{
    _size_map = _settings.size();
    _font.loadFromFile("./Sfml/Assets/Timeless.ttf");
    for (std::map<std::string, bool>::iterator it = settings.begin(); it != settings.end(); it++) {
        sf::Text newText(it->first, _font, 15);
        newText.setFillColor(sf::Color::Black);
        newText.setPosition(sf::Vector2f(posWin.x - _vm.width, posWin.y));
        _txt.push_back(newText);
    }
    for (int i = 0; i < _size_map; i++) {
        sf::RectangleShape button;
        button.setFillColor(sf::Color::White);
        button.setSize(sf::Vector2f(15, 15));
        button.setOutlineThickness(1.5f);
        button.setOutlineColor(sf::Color::Blue);
        button.setPosition(sf::Vector2f(130, 15 * i));
        _buttons.push_back(button);
    }
}

GraphicMenu::~GraphicMenu()
{
}

void GraphicMenu::getEvent()
{
    while(_rwindow.pollEvent(_evt)) {
        if (_evt.type == sf::Event::KeyPressed) {
            if (_evt.key.code == sf::Keyboard::Escape)
                _rwindow.close();
        }
        if (_evt.type == sf::Event::MouseButtonPressed) {
            // if (isClickedOnButton(_evt.mouseButton.x, _evt.mouseButton.y, _buttons)) {

            // }
        }
    }
}

void GraphicMenu::draw()
{
    sf::Vector2f pos(0, 0);
    _rwindow.clear(sf::Color::White);
    for (sf::Text a : _txt) {
        a.setPosition(pos);
        pos.y += 15;
        _rwindow.draw(a);
    }
    _rwindow.display();
}

void GraphicMenu::menu()
{
    while (_rwindow.isOpen()) {
        getEvent();
        draw();
    }
}
