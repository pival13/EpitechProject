/*
** EPITECH PROJECT, 2020
** Cursor.hpp
** File description:
** cursor
*/

#pragma once

// Project includes
#include "SfmlTools.hpp"
#include "TextureBase.hpp"

class Jam::Cursor
{
public:
    Cursor();
    ~Cursor();

    void compute(sf::Event & event);
    void display(sf::RenderWindow & window);
    void execute(sf::RenderWindow & window, sf::Event & event);

    void animate();

    static sf::Vector2i getPosition() { return pos; };
    static void setPosition(const sf::Vector2i & v);
    static sf::Vector2i pos;

private:
    sf::Sprite _sprite;
    sf::Sprite _sprite2;
    sf::Time _time;
};
