/*
** By Kevin Pruvost, May 2020
** File description:
** Menu class.
*/

#pragma once

// Project includes
#include "Page.hpp"
#include "ResourceDatabase.hpp"
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <cmath>

/**
 * @brief Contains the menu page interactions.
 */
class Menu : virtual public Page
{
public:
	Menu(ZappyRenderWindow & window);
	~Menu();

    /**
     * @brief Override of Page::compute().
     * @param window
     * @param event
     * @param client
     * @return int
     */
    int compute(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client);
    /**
     * @brief Override of Page::compute().
     * @param window
     * @param event
     * @param client
     * @return int
     */
    int draw(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client);

private:
    void animateBackground(float speed);
    void checkCursorHighlight();

private:
    KVector<Object> _objects;

    InterfaceObject _title;
    InterfaceObject _planet;
    InterfaceObject _background;
    InterfaceObject _play;
    InterfaceObject _quit;

    Cursor _cursor;
};
