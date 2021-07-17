/*
** EPITECH PROJECT, 2020
** RType_2020
** File description:
** End
*/

#ifndef END_HPP_
#define END_HPP_

#include "AScene.hpp"

class End : public AScene
{
    public:
        End();
        ~End();

        void getEvents(game_t *, sf::RenderWindow *);
        void updateGame(game_t *, sf::RenderWindow *);
        void drawGame(game_t *, sf::RenderWindow *);

    private:
        sf::Sprite _bg;
        sf::Time _time;
};

#endif /* !END_HPP_ */