/*
** EPITECH PROJECT, 2020
** Player.cpp
** File description:
** Player
*/

#include <iostream>
#include "Player.hpp"

using namespace Jam;

bool Player::isPlayerDead = true;

Player::Player()
    : Character(true)
{
    Player::isPlayerDead = false;
}

Player::~Player()
{
    Player::isPlayerDead = true;
}

void Player::move()
{
}

void Player::checkMouse(sf::Event & event)
{
    if (Cursor::getPosition().x != ring1.area.getPosition().x || Cursor::getPosition().y != ring1.area.getPosition().y)
        moveSprite(event);
    resetTime(_time);
}

void Player::compute(sf::Event & event)
{
    checkMouse(event);
    resetTime(_time);
}

float Player::determineX()
{
    return (Cursor::getPosition().x - ring1.area.getPosition().x) * 0.0015;
}

float Player::determineY()
{
    return (Cursor::getPosition().y - ring1.area.getPosition().y) * 0.0015;
}

void Player::draw(sf::RenderWindow & window)
{
    window.draw(blackHole);
    ring1.draw(window);
    ring2.draw(window);
    ring3.draw(window);
    ring4.draw(window);
}

sf::Vector2f Player::getSpeed()
{
    return sf::Vector2f(_x, _y);
}

void Player::moveSprite(sf::Event & event)
{
    int ms = getMs(_time);
    float X = determineX();
    float Y = determineY();
    if (X > 0.8)
        X = 0.8;
    if (X < -0.8)
        X = -0.8;
    if (Y > 0.8)
        Y = 0.8;
    if (Y < -0.8)
        Y = -0.8;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        X *= _sprint;
        Y *= _sprint;
        _sprint += 0.0001;
        //if (_sprint > 2.5)
        //    _sprint = 2.5;
    }
    else {
        _sprint = 1;
    }
    _x = ms * X;
    _y = ms * Y;
    ring1.move(ms * X, ms * Y);
    ring2.move(ms * X, ms * Y);
    ring3.move(ms * X, ms * Y);
    ring4.move(ms * X, ms * Y);
    blackHole.move(ms * X, ms * Y);
}
