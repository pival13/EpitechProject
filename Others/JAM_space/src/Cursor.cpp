/*
** EPITECH PROJECT, 2020
** Cursor.cpp
** File description:
** cursor
*/

#include "Cursor.hpp"

#include <iostream>

using namespace Jam;

sf::Vector2i Cursor::pos = sf::Mouse::getPosition();

Cursor::Cursor()
{
    _sprite.setTexture(textureBase[TextureId::CURSOR]);
    _sprite2.setTexture(textureBase[TextureId::CURSOR]);
    auto rect = _sprite.getTextureRect();
    rect.width /= 2;
    _sprite.setTextureRect(rect);
    _sprite2.setTextureRect(rect);
    rect.left = rect.width;
    _sprite2.setTextureRect(rect);
    sf::Mouse::setPosition({(int)DesktopMode.width / 2, (int)DesktopMode.height / 2});
}

Cursor::~Cursor()
{
}

void Cursor::animate()
{
    static bool sens = false;
    auto color = _sprite.getColor();

    (!sens) ? --color.a : ++color.a;
    if (color.a <= 0 || color.a >= 255)
        sens = !sens;
    _sprite.setColor(color);
}

void Cursor::compute(sf::Event &)
{
    // Moving cursor.
    const auto mousePos = sf::Mouse::getPosition();

    auto spritePos = pos;

    spritePos.x += mousePos.x - ((int)DesktopMode.width / 2);
    spritePos.y += mousePos.y - ((int)DesktopMode.height / 2);
    //std::cout << mousePos.x - ((int)DesktopMode.width / 2) << " " << mousePos.y - ((int)DesktopMode.height / 2)<< std::endl;
    _sprite.setPosition(spritePos.x, spritePos.y);
    _sprite2.setPosition(spritePos.x, spritePos.y);

    pos.x = spritePos.x;
    pos.y = spritePos.y;

    sf::Mouse::setPosition({(int)DesktopMode.width / 2, (int)DesktopMode.height / 2});

    if (getMs(_time) >= 5)
    {
        animate();
        resetTime(_time);
    }
}

void Cursor::display(sf::RenderWindow & window)
{
    window.draw(_sprite2);
    window.draw(_sprite);
}

void Cursor::execute(sf::RenderWindow & window, sf::Event & event)
{
    compute(event);
    display(window);
}

void Cursor::setPosition(const sf::Vector2i & v)
{
    pos = v;
}