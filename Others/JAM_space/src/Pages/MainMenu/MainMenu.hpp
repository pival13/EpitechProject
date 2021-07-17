/*
** EPITECH PROJECT, 2020
** MainMenu.hpp
** File description:
** main menu
*/

#pragma once

// Project includes
#include "SfmlTools.hpp"

#include "Button.hpp"
#include "Title.hpp"

#include "IPage.hpp"

class Jam::MainMenu : virtual public IPage
{
public:
    MainMenu();
    ~MainMenu();

public:
    void execute(sf::RenderWindow & window, sf::Event & event) override;
    void executeChangePage(sf::RenderWindow & window, sf::Event & event) override;

private:
    void display(sf::RenderWindow & window);
    void compute(sf::Event & event, sf::RenderWindow & window);

private:
    std::vector<Jam::Button> _buttons;
    Jam::Title _title;
};