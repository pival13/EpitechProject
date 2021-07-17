/*
** By Kevin Pruvost, May 2020
** File description:
** MainWindow class.
*/

#pragma once

// Project includes
#include "Game.hpp"
#include "Menu.hpp"

/**
 * @brief Contains the main window, processes everything.
 */
class MainWindow
{
public:
	MainWindow(const std::string & ip, const std::string & port);
	~MainWindow();

	/**
	 * @brief To launch in the main to make the MainWindow object work.
	 * @return int
	 */
	int exec();

private:
	void createPages();
	void playingMusic();

private:
    ZappyRenderWindow _window;
    sf::Event _event;

	KVector<std::unique_ptr<IPage>> _pages;
	PageId _pageId = PageId::MENU_PAGE;

	GraphicalClient _client;
};