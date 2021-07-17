/*
** EPITECH PROJECT, 2020
** Pause.cpp
** File description:
** pause
*/

#include "Pause.hpp"

using namespace Jam;

Pause::Pause()
{
    _buttons.push_back(Button("Resume", 0.5, 1.f/3));
    _buttons.push_back(Button("Quit", 0.5, 2.f/3));
}

Pause::~Pause()
{
}

void Pause::execute(sf::RenderWindow & window, sf::Event & event)
{
    compute(event, window);
    display(window);
}

void Pause::executeChangePage(sf::RenderWindow & window, sf::Event & event)
{
    window.setView(window.getDefaultView());
    sf::Vector2i vec = {(int)window.getView().getCenter().x,
                        (int)window.getView().getCenter().y};
    Cursor::setPosition(vec);
    for (auto & button : _buttons)
        button.pageCheck();
    resetTime(_time);
}

void Pause::display(sf::RenderWindow & window)
{
    for (const auto & button : _buttons)
        button.display(window);
}

void Pause::compute(sf::Event & event, sf::RenderWindow & window)
{
    for (auto & button : _buttons)
        button.compute(event);
    if (_buttons[0].isClick(event))
        pageId = Pages::GAME;
    if (_buttons[1].isClick(event))
        window.close();

    if (event.key.code == sf::Keyboard::Escape && event.type == sf::Event::KeyReleased)
    {
        event.type = sf::Event::KeyPressed;
        pageId = Pages::GAME;
    }
}