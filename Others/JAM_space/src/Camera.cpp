/*
** EPITECH PROJECT, 2020
** JAM_space_2019
** File description:
** Camera
*/

#include "Camera.hpp"

using namespace Jam;

Camera::Camera()
{
    _view.setCenter(sf::Vector2f({BORDER_X / 2, BORDER_Y / 2}));
    _view.setSize(sf::Vector2f(BORDER_X, BORDER_Y));
}

Camera::~Camera()
{
}

sf::View& Camera::getView()
{
    return _view;
}

#include <iostream>

void Camera::update(sf::Vector2f pos, sf::Vector2f posHole)
{
    static float scale = 0.4;
    top = _view.getCenter().y - ((_view.getSize().y / 2) * scale);
    bot = _view.getCenter().y + ((_view.getSize().y / 2) * scale);
    left = _view.getCenter().x - ((_view.getSize().x / 2) * scale);
    right = _view.getCenter().x + ((_view.getSize().x / 2) * scale);

    //sf::Vector2f mouse(Cursor::getPosition());
    //std::cout << left << "\t" << right << "\t" << top << "\t" << bot << "\n"; 
    //std::cout << posHole.x << "\t" << posHole.y << std::endl; 
    if (posHole.y < top || posHole.y > bot || posHole.x > right || posHole.x < left) {
        _view.move(pos.x, pos.y);
        //_view.setCenter(_view.getCenter().x + pos.x, _view.getCenter().y + pos.y);
    }
    else
    {
       // std::cout << "CA DEVRAIT PAS" << std::endl;
    }
    
}