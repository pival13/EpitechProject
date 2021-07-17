/*
** EPITECH PROJECT, 2020
** Game.hpp
** File description:
** game
*/

#pragma once

// Project includes
#include "IPage.hpp"

#include "TextureBase.hpp"

#include "SfmlTools.hpp"
#include "Camera.hpp"
#include "Characters/Player.hpp"
#include "Characters/AI.hpp"
#include "Collision.hpp"
#include "Factory.hpp"

class Jam::Game : virtual public IPage
{
public:
    Game();
    ~Game();

public:
    void createEnnemi(size_t, size_t, size_t);
    void createBoss(size_t, size_t);
    void execute(sf::RenderWindow & window, sf::Event & event) override;
    void executeChangePage(sf::RenderWindow & window, sf::Event & event) override;
private:
    void setPositionEnnemi();
    void setNutritiveValue(size_t, size_t);
    void setScaleEnnemi();
    void display(sf::RenderWindow & window);
    void compute(sf::Event & event);
private:
    std::list<std::unique_ptr<Jam::AEatable>> _characters;
    std::unique_ptr<Jam::Camera> cam;
    Jam::AEatable * _player = nullptr;
    sf::Vector2i _pos;
};
