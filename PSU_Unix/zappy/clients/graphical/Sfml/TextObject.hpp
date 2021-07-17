/*
** By Kevin Pruvost, June 2020
** File description:
** TextObject class.
*/

#pragma once

// Project includes
#include "ResourceDatabase.hpp"

/**
 * @brief Inherits from sf::Text and is aimed to use the Constants namespace in an easier way.
 */
class TextObject : public sf::Text
{
public:
	TextObject(Constants::FontId id, const std::string & string = "");
	TextObject(Constants::FontId id, const std::string & string, int x, int y);
	TextObject(Constants::FontId id, const std::string & string, const sf::Vector2f & vec);
	~TextObject();

public:
	std::string text;
	sf::Font * font = nullptr;
	Constants::FontId fontId = Constants::FontId::TOTAL_FONT;
	sf::Vector2i pos = {0, 0};

private:
};