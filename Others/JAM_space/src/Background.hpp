/*
** EPITECH PROJECT, 2020
** Background.hpp
** File description:
** background
*/

#ifndef BACKGROUND_HPP_
#define BACKGROUND_HPP_

// Project includes
#include "Sfml.hpp"
#include "Jam.hpp"
#include "SfmlTools.hpp"

// C++ Includes
#include <cmath>

// INTERACT WITH THE BACKGROUND WITH THESES

#define STAR_INCREMENT 0.2f         // THIS IS THE VALUE OF THE INCREASE/DECREASE OF STARS RADIUSES
#define STAR_SIZE 3.0f              // THIS IS THE MAX STAR SIZE
#define GROWTH_CHANCE 4            // THIS IS THE CHANCE THAT THE STAR CHANGE SIZE THIS ROUND : THE ACTUAL CHANCE IS: 1 / GROWTH_CHANCE

class Jam::BackgroundStar {
    public:
        BackgroundStar();
        ~BackgroundStar();

        void changeSize();
        float getSize();
        void setPosition(sf::Vector2f &pos);
        void setPosition(sf::Vector2u &wdwSize);
        bool isGrowing();
        sf::CircleShape &getShape();
        void move(const sf::Vector2f &vector);
    //private ?
    private:
        bool growing;
        sf::CircleShape shape;
        float size;
        sf::Vector2f pos;

};

class Jam::Background
{
    public:
        Background(sf::Vector2u wdwSize);
        ~Background();

        void printStars(sf::RenderWindow &wdw);
        void move(const sf::Vector2f & vector);
        
    // private ?
    private:
        void changeStarsSizes();

        std::vector<Jam::BackgroundStar> stars;
        sf::Vector2u wdwSize;
        size_t starsNb;

        sf::Vector2f old;

        sf::Time _time;
};


#endif // BACKGROUND_HPP_