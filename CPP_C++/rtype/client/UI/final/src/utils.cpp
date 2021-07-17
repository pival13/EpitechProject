/*
** EPITECH PROJECT, 2020
** JAM_escape_2019
** File description:
** utils
*/

#include "my.hpp"

bool mouseInButton(sf::Vector2f pos, const sf::Sprite &sprite)
{
    sf::FloatRect rect = sprite.getGlobalBounds();

    if (pos.x >= rect.left && pos.x <= rect.left + rect.width &&
        pos.y >= rect.top && pos.y <= rect.top + rect.height)
        return true;
    return false;
}

bool mouseInArea(sf::Vector2f pos, const sf::FloatRect &rect)
{
    if (pos.x >= rect.left && pos.x <= rect.left + rect.width &&
        pos.y >= rect.top && pos.y <= rect.top + rect.height)
        return true;
    return false;
}

bool mouseIsPressed(sf::Event event)
{
    if (event.type == sf::Event::MouseButtonPressed)
        return true;
    return false;
}