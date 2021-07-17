/*
** By Kevin Pruvost, June 2020
** File description:
** TeamButton class.
*/

#pragma once

// Project includes
#include "BottomButton.hpp"

/**
 * @brief Button designed to be clicked to get a team's informations.
 */
class TeamButton : public BottomButton
{
public:
	TeamButton(const std::string & str, sf::Color teamColor, int x = 0, int y = 0);
	~TeamButton();

private:
};