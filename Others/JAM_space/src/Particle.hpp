/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Particle
*/

#pragma once

#include "Sfml.hpp"
#include <vector>

namespace Jam {
    class ParticleGenerator;
    class Particle {
        public:
            Particle(float x, float y, float size, ParticleGenerator *parent, const sf::Color &color);
            ~Particle();

            void draw(sf::RenderWindow &) const;
            void move();

        private:
            sf::CircleShape circle;
            ParticleGenerator &parent;
            sf::Vector2f moveVector;
    };

    class ParticleGenerator {
        public:
            ParticleGenerator(sf::Vector2f orig1, sf::Vector2f scale, float radius, float borderWidth, float rotation, float density, const sf::Color color);
            ~ParticleGenerator();

            void setScale(float);
            float getScale() const;

            void draw(sf::RenderWindow &) const;
            void move(float x, float y);

            sf::CircleShape area;
            const float min_radius;
            const float rotate;

        private:
            const float density;
            sf::Color color;
            sf::Vector2f offset;
            sf::Vector2f initScale;
            sf::Vector2f moveVector;
            std::vector<Particle *> particles;
    };
};