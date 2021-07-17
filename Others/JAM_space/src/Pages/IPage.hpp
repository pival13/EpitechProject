/*
** EPITECH PROJECT, 2020
** Page.hpp
** File description:
** page
*/

#pragma once

// Project includes
#include "SfmlTools.hpp"

class IPage
{
    public:
        virtual ~IPage() = default;

        virtual void execute(sf::RenderWindow & window, sf::Event & event) = 0;
        virtual void executeChangePage(sf::RenderWindow & window, sf::Event & event) = 0;
};