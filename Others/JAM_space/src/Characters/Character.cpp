/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Characters
*/

#include "Character.hpp"
#include <cmath>
#include <iostream>

using namespace Jam;

Character::Character(bool isPlayer)
    : ring1(sf::Vector2f(BORDER_X / 2, BORDER_Y / 2),sf::Vector2f(1.5, 0.7), 85, 20, 0.002, 2, isPlayer ? sf::Color(0xff9800ff) : sf::Color::Red),
    ring2(sf::Vector2f(BORDER_X / 2, BORDER_Y / 2),sf::Vector2f(1.5, 0.7), 85, 20, 0.002, 2, isPlayer ? sf::Color::Yellow : sf::Color::Red),
    ring3(sf::Vector2f(BORDER_X / 2, BORDER_Y / 2),sf::Vector2f(1.5, 0.7), 85, 20, 0.002, 1, isPlayer ? sf::Color(0xd4d4d4FF) : sf::Color::Red),
    ring4(sf::Vector2f(BORDER_X / 2, BORDER_Y / 2),sf::Vector2f(1.5, 0.7), 95, 30, 0.002, 0.8, isPlayer ? sf::Color(0xff9800ff) : sf::Color::Red),
    blackHole(75), _time ( sf::milliseconds(0) )
{
    blackHole.setScale(1.5, 0.7);
    blackHole.setFillColor(sf::Color::Black);
    blackHole.setOrigin(75,75);
    blackHole.setPosition(BORDER_X / 2, BORDER_Y / 2);
    _nutritiveValue = 10;
}

Character::~Character()
{
}

const sf::Vector2f & Character::getPosition()
{
    pos.x = blackHole.getGlobalBounds().left + blackHole.getGlobalBounds().width / 2;
    pos.y = blackHole.getGlobalBounds().top + blackHole.getGlobalBounds().height / 2;

    return pos;
}

void Character::setPosition(sf::Vector2f& Pos)
{
    ring1.area.setPosition(Pos);
    ring2.area.setPosition(Pos);
    ring3.area.setPosition(Pos);
    ring4.area.setPosition(Pos);
    blackHole.setPosition(Pos);
}

void Character::checkMouse(sf::Event & event)
{
}

void Character::move()
{
}

void Character::draw(sf::RenderWindow & window)
{

}

void Character::compute(sf::Event & e)
{
    move();
    checkMouse(e);
    resetTime(_time);
}

void Character::resetTimeD()
{
    resetTime(_time);
}

bool Character::eat(AEatable &target)
{
    _nutritiveValue += target.getNutritiveValue() / 2;
    setScale(log10(_nutritiveValue));
    return true;
}

// Getters and setters ---------------------------------------------------------

void Character::setScale(float scale)
{
    ring1.setScale(scale);
    ring2.setScale(scale);
    ring3.setScale(scale);
    ring4.setScale(scale);
    blackHole.setScale(sf::Vector2f(1.5, 0.7) * scale);
}

float Character::getScale(void) const { return ring1.getScale(); }

sf::FloatRect Character::getGlobalBounds() const { return blackHole.getGlobalBounds();}
