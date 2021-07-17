/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** AI
*/

#include "AI.hpp"

using namespace Jam;

Jam::AI::AI()
: Character(false), direction((float)(rand()%14000-7000)/10000.f,(float)(rand()%14000-7000)/10000.f)
{
    getNutritiveValue() = 8;
}

Jam::AI::~AI()
{
}

void AI::getMoving(float x, float y)
{
    int ms = getMs(_time);

    ring1.move(x * ms, y * ms);
    ring2.move(x * ms, y * ms);
    ring3.move(x * ms, y * ms);
    ring4.move(x * ms, y * ms);
    blackHole.move(x * ms, y * ms);
    resetTime(_time);
}

void AI::randomMove()
{
    int ms = getMs(_time);

    direction.x += (float)(rand() % 10000-5000) / 100000.f;
    direction.y += (float)(rand() % 10000-5000) / 100000.f;
    if (direction.x > 0.5)
        direction.x = 0.5;
    if (direction.x < -0.5)
        direction.x = -0.5;
    if (direction.y > 0.5)
        direction.y = 0.5;
    if (direction.y < -0.5)
        direction.y = -0.5;
    ring1.move(direction.x*ms, direction.y*ms);
    ring2.move(direction.x*ms, direction.y*ms);
    ring3.move(direction.x*ms, direction.y*ms);
    ring4.move(direction.x*ms, direction.y*ms);
    blackHole.move(direction.x*ms, direction.y*ms);
    resetTime(_time);
}

void AI::moveAI(std::list<std::unique_ptr<AEatable>> & obj)
{
    sf::Vector2f pos(blackHole.getGlobalBounds().left + blackHole.getGlobalBounds().width / 2, 
                     blackHole.getGlobalBounds().top + blackHole.getGlobalBounds().height / 2);

    float x = 0;
    float y = 0;
    float saveValue, savex, savey = 0;
    //static AEatable *target = nullptr;

    //if (target != nullptr) {
    //    x = (target->getGlobalBounds().left + target->getGlobalBounds().width / 2) - pos.x;
    //    y = (target->getGlobalBounds().top + target->getGlobalBounds().height / 2) - pos.y;
    //} else
        for (std::unique_ptr<AEatable> &i : obj) {
            if ((saveValue = i->getNutritiveValue()) < this->getNutritiveValue() * 0.9) {
                savex = (i->getGlobalBounds().left + i->getGlobalBounds().width / 2) - pos.x;
                savey = (i->getGlobalBounds().top + i->getGlobalBounds().height / 2) - pos.y;
                if ((x == 0 && y == 0) || (savex*savex+savey*savey < x*x+y*y)) {
                    x = savex;
                    y = savey;
      //              target = i.get();
                }
            }
        }

    if (x == 0 && y == 0)
        randomMove();
    else
        getMoving(x * 0.0012, y * 0.0012);
}

void AI::draw(sf::RenderWindow & window)
{
    window.draw(blackHole);
    ring1.draw(window);
    ring2.draw(window);
    ring3.draw(window);
    ring4.draw(window);
}