/*
** EPITECH PROJECT, 2020
** RType_2020
** File description:
** AScene
*/

#ifndef ASCENE_HPP_
#define ASCENE_HPP_

#include "my.hpp"

class AScene
{
    public:
        AScene(page_t page);
        virtual ~AScene();

        virtual void getEvents(game_t *, sf::RenderWindow *)= 0;
        virtual void updateGame(game_t *, sf::RenderWindow *)= 0;
        virtual void drawGame(game_t *, sf::RenderWindow *)= 0;

        page_t getPage();
    private:
        page_t _pageName;
};

#endif /* !ASCENE_HPP_ */