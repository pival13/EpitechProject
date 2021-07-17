/*
** EPITECH PROJECT, 2020
** Player.hpp
** File description:
** Player class
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

// Project includes
#include "Sfml.hpp"
#include "Jam.hpp"
#include "SfmlTools.hpp"

#include "Character.hpp"
#include "../Particle.hpp"

class Jam::Player : virtual public Jam::Character
{
    public:
        Player();
        ~Player();
        
        void checkMouse(sf::Event &) override;
        void moveSprite(sf::Event & event);
        void move() override;
        void moveUp(sf::Time & time);
        void moveDown(sf::Time & time);
        void moveRight(sf::Time & time);
        void moveLeft(sf::Time & time);
        void moveUpLeft(sf::Time & time);
        void moveUpRight(sf::Time & time);
        void moveDownLeft(sf::Time & time);
        void moveDownRight(sf::Time & time);
        float determineX();
        float determineY();

        static bool isPlayerDead;

        void compute(sf::Event & event) override;
        
        void draw(sf::RenderWindow &) override;

        sf::Vector2f getSpeed();
    private:
        float _sprint = 1;
        float _x = 0;
        float _y = 0;
};

#endif /* !PLAYER_HPP_ */
