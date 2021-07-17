/*
** By Kevin Pruvost, May 2020
** IPage.hpp
** File description:
** con
*/

#pragma once

// Project includes
#include "ZappyRenderWindow.hpp"
#include "SfmlIncludes.hpp"
#include "GraphicalClient.hpp"

/**
 * @brief Page Interface.
 */
class IPage
{
public:
    ~IPage() = default;
    virtual int compute(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client) = 0;
    virtual int draw(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client) = 0;
};