/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Character
*/

#ifndef CHARACTER_HPP_
#define CHARACTER_HPP_

// Project includes
#include "Sfml.hpp"
#include "Jam.hpp"
#include "AEatable.hpp"
#include "SfmlTools.hpp"
#include "Particle.hpp"

class Jam::Character : virtual public AEatable
{
    public:
        Character(bool isPlayer);
        ~Character();
        float getScale() const;
        void setScale(float);
        void setPosition(sf::Vector2f&);
        const sf::Vector2f & getPosition() override;
        sf::FloatRect getGlobalBounds() const;

        virtual void compute(sf::Event & event);
        virtual void move();
        virtual void checkMouse(sf::Event & event);
        virtual void draw(sf::RenderWindow &);
        bool eat(AEatable &);

        void resetTimeD() override;
    protected:
        ParticleGenerator ring1;
        ParticleGenerator ring2;
        ParticleGenerator ring3;
        ParticleGenerator ring4;
        sf::CircleShape blackHole;

        sf::Time _time;
        sf::Vector2f pos;
};

#endif /* !CHARACTER_HPP_ */
