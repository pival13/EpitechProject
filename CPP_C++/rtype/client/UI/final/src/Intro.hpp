/*
** EPITECH PROJECT, 2020
** RType_2020
** File description:
** Intro
*/

#ifndef INTRO_HPP_
#define INTRO_HPP_

#include "AScene.hpp"

class Intro : public AScene
{
    public:
        Intro();
        ~Intro();

        void drawGame(game_t *, sf::RenderWindow *);
        void updateGame(game_t *, sf::RenderWindow *);
        void getEvents(game_t *, sf::RenderWindow *);
    private:
        std::vector<sf::Sprite> _spriteList;
        int _indexSprite;
        sf::Time _time;
};

#endif /* !INTRO_HPP_ */
