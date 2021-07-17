/*
** By Kevin Pruvost, May 2020
** File description:
** GameBackground class.
*/

#include "GameBackground.hpp"

GameBackground::GameBackground(Constants::TextureId tId)
    : InterfaceObject(tId, 0, 0)
{
    setOrigin(texture->getSize().x / 2, texture->getSize().y / 2);
}

GameBackground::~GameBackground()
{

}

void GameBackground::animateBackground(float speed)
{
    static auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    auto elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    if (elapsedMs >= speed)
    {
        start = std::chrono::steady_clock::now();
        pos.x += texture->getSize().x / 1000;
        if (pos.x >= (int)texture->getSize().x / 2)
            pos.x -= texture->getSize().x / 2;
    }
    setPosition();
}

void GameBackground::moveBackground(int x, int y)
{
    _basePos.x += x;
    _basePos.y += y;
    setPosition();
}

void GameBackground::setPosition(int x, int y)
{
    _basePos.x = x;
    _basePos.y = y;
    setPosition();
}

void GameBackground::setPosition()
{
    Object::setPosition(_basePos.x + pos.x - (texture->getSize().x / 2),
                        _basePos.y + pos.y - (texture->getSize().y / 2));
}