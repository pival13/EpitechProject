/*
** EPITECH PROJECT, 2020
** JAM_space_2019
** File description:
** Eatable
*/

#include "Eatable.hpp"

using namespace Jam;

Eatable::Eatable(sf::Texture & pTexture)
    : _texture {pTexture}
{
    _sprite.setTexture(_texture);
}

Eatable::~Eatable() = default;

void Eatable::compute(sf::Event &pEvent)
{
}

void Eatable::draw(sf::RenderWindow &pWin)
{
    pWin.draw(_sprite);
}

bool Eatable::eat(AEatable &)
{
    return false;
}

float Eatable::getScale() const
{
    return _sprite.getScale().x;
}

sf::FloatRect Eatable::getGlobalBounds() const
{
    return _sprite.getGlobalBounds();
}

void Eatable::setPosition(sf::Vector2f& Pos)
{
    this->_sprite.setPosition(Pos);
}

void Eatable::setScale(float scale)
{
    this->_sprite.scale(scale, scale);
}
