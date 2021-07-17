/*
** EPITECH PROJECT, 2020
** RType_2020
** File description:
** Intro
*/

#include "Intro.hpp"

Intro::Intro()
: AScene(INTRO), _indexSprite(0)
{
    std::string dir = __FILE__;
    dir = dir.substr(0, dir.find_last_of("\\/"));
    for (int i = 0; i <= 249; i++) {
        sf::Texture *texture = new sf::Texture();
        sf::Sprite sprite = sf::Sprite();
        sprite.setPosition(1920 / 2 - 400, 1080 / 2 - 300);
        std::string nbr = std::to_string(i);
        std::string str = dir + "/../gifloading-0/gifloading-" + nbr + ".png";

        texture->loadFromFile(str);
        sprite.setTexture(*texture);
        sprite.setScale(1.f, 1.f);
        sprite.getPosition();
        _spriteList.push_back(sprite);
    }
}

Intro::~Intro()
{
}

void Intro::drawGame(game_t *gm, sf::RenderWindow *window)
{
    _time = gm->clock.getElapsedTime();
    sf::RectangleShape *bg_gif = new sf::RectangleShape(sf::Vector2f(1920, 1080));
    bg_gif->setFillColor(sf::Color(18, 25, 33));

    if (_indexSprite < 249) {
        if (_time.asSeconds() >= 0.04f) {
            window->draw(*bg_gif);
            window->draw(_spriteList[_indexSprite]);
            gm->clock.restart();
            _indexSprite++;
        }
    }
}

void Intro::updateGame(game_t *gm, sf::RenderWindow *)
{
    if (_indexSprite == 249)
        gm->nextPage = MENU;
}

void Intro::getEvents(game_t *, sf::RenderWindow *)
{
}
