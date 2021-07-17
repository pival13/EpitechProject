/*
** EPITECH PROJECT, 2020
** Button.hpp
** File description:
** button
*/

#pragma once

#include "SfmlTools.hpp"
#include "TextureBase.hpp"

#include "Cursor.hpp"

#define BUTTON_TEXT_COLOR  0x06902Bff
#define BUTTON_TEXT1_COLOR 0x0000009C

class Jam::Button
{
public:
    Button(const std::string & text, float x, float y);
    ~Button();

public:
    void pageCheck();
    void display(sf::RenderWindow & window) const;
    void compute(sf::Event & event);
    void animate(sf::Event & event);
    void unanimate(sf::Event & event);

    bool isClick(sf::Event & event);

private:
    sf::Sprite _sprite;
    sf::Text   _text;
    sf::Text   _text1;

    sf::Time _time;
    sf::Time timeDraw;
};
