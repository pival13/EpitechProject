/*
** EPITECH PROJECT, 2020
** JAM_space_2019
** File description:
** Eatable
*/

#ifndef EATABLE_HPP_
#define EATABLE_HPP_

#include "Sfml.hpp"
#include "Jam.hpp"

#include "Cursor.hpp"

class Jam::AEatable
{
public:
    AEatable();
    virtual ~AEatable() = default;
    size_t& getNutritiveValue();
    virtual void resetTimeD() {}
    virtual void setScale(float) = 0;
    virtual float getScale() const = 0;
    virtual const sf::Vector2f & getPosition() = 0;
    virtual void compute(sf::Event &pEvent) = 0;
    virtual void draw(sf::RenderWindow &pWindow) = 0;
    virtual sf::Vector2f getSpeed();
    virtual sf::FloatRect getGlobalBounds() const = 0;
    virtual void edibleCheck(sf::RenderWindow & pWin, sf::Event & pEvent);
    virtual void setPosition(sf::Vector2f&) = 0;
    virtual bool eat(AEatable &) = 0;

protected:
    size_t _nutritiveValue;
};

#endif /* !EATABLE_HPP_ */
