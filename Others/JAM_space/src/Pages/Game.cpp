/*
** EPITECH PROJECT, 2020
** Game.cpp
** File description:
** game
*/

#include "Game.hpp"
#include <iostream>
#include <cmath>

using namespace Jam;

Game::Game()
{
    // Filling characters.
    cam = std::unique_ptr<Camera>(new Camera());
    createEnnemi(20, 1, 10);
    _characters.push_back(std::unique_ptr<Jam::AEatable>(new AI()));
}

Game::~Game()
{
}

void Game::compute(sf::Event & event)
{
    static int index = 1;

    int old_size = this->_characters.size();

    for (const auto & character : _characters)
    {
        AI *ai = dynamic_cast<AI *>(character.get());
        if (ai)
            ai->moveAI(_characters);
        character->compute(event);
    }
    Jam::Collision::perform_collision(_characters);
    if (Player::isPlayerDead)
        return;
    if ((int)this->_characters.size() != old_size) {
        if (this->_player->getNutritiveValue() <= (size_t)(index * 20)) {
            if (rand() % 10 == 0) {
                _characters.push_front(std::unique_ptr<AEatable>(new AI()));
                _characters.front()->getNutritiveValue() += _characters.back()->getNutritiveValue() / 2;
                _characters.front()->setScale(log10(_characters.front()->getNutritiveValue()));
            } else
                createEnnemi(1, 1, 10);
        } else {
            std::cout << this->_player->getNutritiveValue() << std::endl;    
            createBoss(5, 6);
            ++index;
        }
    }

    if (event.key.code == sf::Keyboard::Escape && event.type == sf::Event::KeyReleased)
    {
        event.type = sf::Event::KeyPressed;
        pageId = Pages::PAUSE;
        _pos = Cursor::getPosition();
    }
}

void Game::display(sf::RenderWindow & window)
{
    for (const auto & character : _characters)
    {
        character->draw(window);
    }
}

void Game::execute(sf::RenderWindow & window, sf::Event & event)
{
    if (Player::isPlayerDead)
    {
        window.close();
        return;
    }
    compute(event);
    if (Player::isPlayerDead)
    {
        window.close();
        return;
    }
    cam->update(_player->getSpeed(), _player->getPosition());
    window.setView(cam->getView());
    display(window);
}

void Game::executeChangePage(sf::RenderWindow & window, sf::Event & event)
{
    if (!_player)
    {
        _characters.push_back(std::unique_ptr<Jam::AEatable>(new Player()));
        _player = _characters.back().get();
        std::cout << _player->getPosition().x << " " << _player->getPosition().y << std::endl;
    }

    Cursor::setPosition(_pos);
    for (auto & character : _characters)
        character->resetTimeD();
    window.setView(cam->getView());
    compute(event);
    display(window);
}

void Game::setPositionEnnemi()
{
    float positionx = 0;
    float positiony = 0;
    int spawnx = 0;
    int spawny = 0;

    if (this->_player == nullptr) {
        positionx = rand() % (int)BORDER_X * 2;
        positiony = rand() % (int)BORDER_Y * 2;
        if (positionx - BORDER_X / 2 < 300)
            positionx += 300 * 1.2;
        if (positiony - BORDER_Y / 2 < 300)
            positiony += 300 * 1.2;
    } else {
        spawnx = rand() % 2;
        spawny = rand() % 2;
        positionx = rand () % (int)BORDER_X * 2;
        if (positionx - _player->getPosition().x < _player->getGlobalBounds().width)
            positionx += _player->getGlobalBounds().width * 1.2;
        positiony = rand () % (int)BORDER_Y * 2;
        if (positiony - _player->getPosition().y < _player->getGlobalBounds().height)
            positiony += _player->getGlobalBounds().height * 1.2;
        if (spawnx == 1)
            positionx *= -1;
        if (spawny == 1)
            positiony *= -1;
    }
    sf::Vector2f pos (positionx, positiony);
    this->_characters.front()->setPosition(pos);
}

void Game::setNutritiveValue(size_t min, size_t max)
{
    size_t nutritiveValue = 0;

    nutritiveValue = rand() % max;
    if (nutritiveValue <= 0)
        nutritiveValue = min;
    this->_characters.front()->getNutritiveValue() = nutritiveValue;
}

void Game::setScaleEnnemi()
{
    this->_characters.front()->setScale(log10(this->_characters.front()->getNutritiveValue() * 0.50));
}

void Game::createBoss(size_t nutritiveMin, size_t nutritiveMax)
{
    _characters.push_front(Factory::createBoss());
    setPositionEnnemi();
    setNutritiveValue(nutritiveMin, nutritiveMax);
    setScaleEnnemi();
}

void Game::createEnnemi(size_t nbrEnnemi, size_t nutritiveMin, size_t nutritiveMax)
{
    for (size_t a = 0; a < nbrEnnemi; ++a) {
        _characters.push_front(Factory::createEatable());
        setPositionEnnemi();
        setNutritiveValue(nutritiveMin, nutritiveMax);
        setScaleEnnemi();
    }
}
