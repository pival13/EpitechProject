/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Particle
*/

#include "Particle.hpp"
#include <iostream>
#include <cmath>
#include <unistd.h>

#define PI 3.1415926535

static float modulo(float x, float y)
{
    if (y < 0)
        y = -y;
    return x - ((long)(x/y)*y);
}

/*********************************/
/*                               */
/*           Particle            */
/*                               */
/*********************************/

Jam::Particle::Particle(float x, float y, float size, Jam::ParticleGenerator *parent, const sf::Color &color)
    : circle(size), parent(*parent)
{
    circle.setFillColor(color);
    circle.setPosition(x, y);
    moveVector.x = (float)(rand() % 100-50) / 1000;
    moveVector.y = (float)(rand() % 100-50) / 1000;
}

Jam::Particle::~Particle() {}

void Jam::Particle::draw(sf::RenderWindow &win) const
{
    sf::CircleShape tmp(circle);
    tmp.setPosition(parent.area.getPosition());
    tmp.move(circle.getPosition().x * parent.area.getScale().x * parent.area.getRadius(), circle.getPosition().y * parent.area.getScale().y * parent.area.getRadius());
    win.draw(tmp);
}

void Jam::Particle::move()
{
    unsigned int r = rand();
    circle.move(moveVector);
    moveVector.x += (r & 0x10000 ? 1 : -1) * ((float)((r & 0xFF) % 100) / 1000);
    moveVector.x = modulo(moveVector.x, 0.001);
    moveVector.y += (r & 0x20000 ? 1 : -1) * ((float)(((r & 0xFF00) >> 8) % 100) / 1000);
    moveVector.y = modulo(moveVector.y, 0.001);
    float d = sqrt(circle.getPosition().x*circle.getPosition().x + circle.getPosition().y*circle.getPosition().y);
    float a = circle.getPosition().y / circle.getPosition().x;
    if (d > 1 || d < -1) {
        float x = sqrt(1 / (a*a+1)) * (circle.getPosition().x < 0 ? 1 : -1);
        float y = a * x;
        circle.setPosition(x, y);
    }
    if (d < parent.min_radius && d > -parent.min_radius) {
        float x = sqrt((parent.min_radius*parent.min_radius) / (a*a+1)) * (circle.getPosition().x < 0 ? 1 : -1);
        float y = a * x;
        circle.setPosition(x, y);    
    }
    circle.setPosition(circle.getPosition().x * cos(parent.rotate) + circle.getPosition().y * sin(parent.rotate),
                       -circle.getPosition().x * sin(parent.rotate) + circle.getPosition().y * cos(parent.rotate));
}

/*********************************/
/*                               */
/*       ParticleGenerator       */
/*                               */
/*********************************/

Jam::ParticleGenerator::ParticleGenerator(sf::Vector2f orig1, sf::Vector2f scale, float radius, float borderWidth, float rotation, float density, const sf::Color color)
    : area(radius), min_radius((radius-borderWidth)/radius), rotate(rotation), density(density), color(color), initScale(scale)
{
    offset.x = rand() % (int)(radius/10) - radius/20;
    offset.y = sqrt(radius/20*radius/20-offset.x*offset.x) * (rand() % 2 * 2 -1);
    area.setPosition(orig1.x + offset.x, orig1.y + offset.y);
    area.setScale(scale);
    moveVector.x = (float)(rand() % 100) / 100;
    moveVector.y = (float)(rand() % 100) / 100;
    sf::CircleShape area2(radius-borderWidth);
    area2.setScale(scale);
    float a = PI * area.getGlobalBounds().width * area.getGlobalBounds().height;
    a -= PI * area2.getGlobalBounds().width * area2.getGlobalBounds().height;
    a /= 2000 / density;
    for (int i = 0; i < a; i++) {
        particles.insert(particles.end(), new Particle((float)(rand() % 100-50) / 100 / PI,(float)(rand() % 100-50) / 100 / PI,((float)(rand()%3+1) / 2), this,color));
    }
}

Jam::ParticleGenerator::~ParticleGenerator()
{
    for (size_t i = 0; i != particles.size(); i++)
        delete particles[i];
}

void Jam::ParticleGenerator::setScale(float scale)
{
    area.setScale(initScale * scale);
    
    sf::CircleShape area2(area.getRadius()*min_radius);
    area2.setScale(initScale*scale);
    float a = PI * area.getGlobalBounds().width * area.getGlobalBounds().height;
    a -= PI * area2.getGlobalBounds().width * area2.getGlobalBounds().height;
    a /= 2000 / density;
    if (a < particles.size())
        for (int i = 0; i < particles.size()-a; i++)
            particles.pop_back();
    else
        for (int i = 0; i < a-particles.size(); i++)
                particles.push_back(new Particle((float)(rand() % 100-50) / 100 / PI,(float)(rand() % 100-50) / 100 / PI,((float)(rand()%3+1) / 2), this,color));
}

float Jam::ParticleGenerator::getScale() const { return area.getScale().x / initScale.x; }

void Jam::ParticleGenerator::draw(sf::RenderWindow &win) const
{
    for (Particle *p : particles) {
        p->move();
        p->draw(win);
    }
}

void Jam::ParticleGenerator::move(float x, float y)
{
    area.move(x, y);
}

/*
void screenshot(sf::RenderWindow &window, const std::string &name)
{
    //sf::Texture t;
    //t.update(window);
    sf::Image image = window.capture();//t.copyToImage();
    if (name.empty())
        image.saveToFile("screenshot.png");
    else
        image.saveToFile(name);
}
*/