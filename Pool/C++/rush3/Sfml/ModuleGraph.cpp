/*
** EPITECH PROJECT, 2020
** cpp_rush3_2019
** File description:
** ModuleGraph
*/

#include "ModuleGraph.hpp"

ModuleGraph::ModuleGraph(IMonitorModule *module)
: _module(*module), _spriteMod(), _spriteModIn()
{
}

ModuleGraph::~ModuleGraph()
{
}

sf::Vector2f calculMidText(int posY, sf::Text text)
{
    sf::Vector2f newVector(0, posY);
    sf::FloatRect textRect = text.getGlobalBounds();
    newVector.x = (180 / 2) - (textRect.width / 2);
    return newVector;
}

void rectToSprite()
{
}

void ModuleGraph::setPos(sf::Vector2f pos)
{
    _pos = pos;
    if (_module.isDrawable()) {
        if (_module.getName() == "Memory") {
            _spriteMod.setPosition(_pos.x, _pos.y);
            _text.setPosition(calculMidText(_pos.y, _text));
            _pos.y += 17;
            int oldX = 0;
            _memSwapArray[0]->setPosition(_pos);
            _memSwapArray[1]->setPosition(_pos);
            oldX += _memSwapArray[1]->getSize().x;
            _pos.x += oldX;
            _memSwapArray[2]->setPosition(_pos);
            oldX += _memSwapArray[2]->getSize().x;
            _pos.x += oldX;
            _memSwapArray[3]->setPosition(_pos);
            _pos.y += 17;
            _pos.x = 0;
            _spriteModIn.setPosition(_pos.x, _pos.y);
            _textSec.setPosition(calculMidText(_pos.y, _textSec));
            _pos.y += 17;
            _memSwapArray[4]->setPosition(_pos);
            _memSwapArray[5]->setPosition(_pos);

        }else if (_module.getName() == "CPU"){
            sf::Vector2f posInit(0, 0);
            _spriteMod.setPosition(_pos.x, _pos.y);
            _spriteModIn.setPosition(_pos.x, _pos.y + 14);
            //_text.setPosition(calculMidText(_pos.y, _text));
            //_pos.y += 38;
            for (Stick *stick : _sticks) {
                stick->_stick.setPosition(stick->_pos.x, _pos.y);
                posInit.x += 5;
            }
        }
    }else {
        _spriteMod.setPosition(_pos.x, _pos.y);
        _text.setPosition(calculMidText(_pos.y, _text));
        if (_module.getName() == "Name" || _module.getName() == "Informations system" || _module.getName() == "Date & Time") {
            _pos.y += 17;
            _spriteModIn.setPosition(_pos.x, _pos.y);
            _textSec.setPosition(calculMidText(_pos.y, _textSec));
        }
    }
}

float calcRange(float cal, float max)
{
    float nbr = (cal * 180) / max;
    return (nbr);
}

int countTab(int tab[])
{
    int i = 0;
    for (; tab[i] != 0 && i < 60; i++);
    return (i);
}

void ModuleGraph::createStick(int tabCPU[60], float max)
{
    sf::Vector2f pos = sf::Vector2f(180, 0);
    for (int i = 0; i < 60; i++) {
        Stick *nvx = new Stick();
        nvx->_color = sf::Color::Cyan;
        nvx->_pos.x = pos.x - (3 * countTab(tabCPU)) + (i * 3);
        nvx->_pos.y = 0;
        nvx->_value = tabCPU[i];
        sf::RectangleShape stick;
        stick.setSize(sf::Vector2f(3.0f, calcRange(nvx->_value, max)));
        stick.setFillColor(nvx->_color);
        nvx->_stick = stick;
        _sticks.push_back(nvx);
        i++;
    }
}