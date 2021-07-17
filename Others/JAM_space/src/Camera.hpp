/*
** EPITECH PROJECT, 2020
** JAM_space_2019
** File description:
** Camera
*/

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "SfmlTools.hpp"
#include "Sfml.hpp"
#include "Jam.hpp"

#include "Cursor.hpp"

class Jam::Camera {
    public:
        Camera();
        ~Camera();
        void update(sf::Vector2f, sf::Vector2f);
        sf::View& getView();
    protected:
        sf::View _view;
    private:
        float left, top, bot, right;
        sf::Time _time;
};

#endif /* !CAMERA_HPP_ */
