/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** AI
*/

#ifndef AI_HPP_
#define AI_HPP_

#include "Character.hpp"
#include "Eatable.hpp"
#include "Sfml.hpp"
#include <list>
#include <cmath>

class Jam::AI : virtual public Jam::Character
{
public:
    AI();
    ~AI();
    void getMoving(float x, float y);
    void randomMove();
    void moveAI(std::list<std::unique_ptr<AEatable>> & _obj);
    void draw(sf::RenderWindow &) override;

private:
    sf::Vector2f direction;
};

#endif /* !AI_HPP_ */
