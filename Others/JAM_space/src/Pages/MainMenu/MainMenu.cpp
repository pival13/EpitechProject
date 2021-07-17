/*
** EPITECH PROJECT, 2020
** MainMenu.cpp
** File description:
** main menu
*/

#include "MainMenu.hpp"

using namespace Jam;

MainMenu::MainMenu()
    : _title { "swallow\nmy junk", 0.5, 0.6f/3 }
{
    _buttons.push_back(Button(" Play", 0.5, 1.7/3));
    _buttons.push_back(Button("Quit", 0.5, 2.5/3));
}

MainMenu::~MainMenu()
{
}

void MainMenu::compute(sf::Event & event, sf::RenderWindow & window)
{
    for (auto & button : _buttons)
    {
        button.compute(event);
    }
    _title.compute(event);
    if (_buttons[0].isClick(event))
        pageId = Pages::GAME;
    if (_buttons[1].isClick(event))
        window.close();
}

void MainMenu::display(sf::RenderWindow & window)
{
    _title.display(window);
    for (const auto & button : _buttons)
        button.display(window);
}

void MainMenu::execute(sf::RenderWindow & window, sf::Event & event)
{
    compute(event, window);
    display(window);
}

void MainMenu::executeChangePage(sf::RenderWindow & window, sf::Event & event)
{
    for (auto & button : _buttons)
        button.pageCheck();
    compute(event, window);
    display(window);
}