/*
** EPITECH PROJECT, 2020
** Pause.hpp
** File description:
** pause
*/

#pragma once

#include "SfmlTools.hpp"
#include "Button.hpp"

#include "Cursor.hpp"

#include "IPage.hpp"

class Jam::Pause : virtual public IPage
{
public:
    Pause();
    ~Pause();

public:
    void execute(sf::RenderWindow & window, sf::Event & event) override;
    void executeChangePage(sf::RenderWindow & window, sf::Event & event) override;

private:
    void display(sf::RenderWindow & window);
    void compute(sf::Event & event, sf::RenderWindow & window);

private:
    std::vector<Jam::Button> _buttons;

    sf::Time _time;
};
