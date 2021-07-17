/*
** EPITECH PROJECT, 2020
** JAM_space_2019
** File description:
** Eatble
*/

#ifndef EATBLE_HPP_
#define EATBLE_HPP_

#include "AEatable.hpp"

class Jam::Eatable : virtual public Jam::AEatable
{
public:
    Eatable(sf::Texture &);
    ~Eatable();
    float getScale() const;
    void setScale(float) override;
    void compute(sf::Event & pEvent) override;
    void draw(sf::RenderWindow & pWindow) override;
    bool eat(AEatable &);
    sf::FloatRect getGlobalBounds() const;
    void setPosition(sf::Vector2f&);
    const sf::Vector2f & getPosition() override { return _sprite.getPosition(); }
protected:
    sf::Sprite _sprite;
    sf::Texture _texture;
};

#endif /* !EATBLE_HPP_ */
