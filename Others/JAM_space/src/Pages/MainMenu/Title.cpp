/*
** EPITECH PROJECT, 2020
** Title.cpp
** File description:
** title
*/

#include "Title.hpp"

using namespace Jam;

Title::Title(const std::string & text, float x, float y)
{
    _sprite.setTexture(textureBase[TextureId::TITLE]);

    _text.setFont(fontBase[FontId::STARSFIGHTERS]);
    _text.setString(text);
    _text.setCharacterSize(35);
    _text.setColor(sf::Color(BUTTON_TEXT_COLOR));
    _text.setOrigin(_text.getLocalBounds().width / 2,
                    _text.getLocalBounds().height / 2);

    _text1.setFont(fontBase[FontId::STARSFIGHTERS]);
    _text1.setString(text);
    _text1.setCharacterSize(35);
    _text1.setColor(sf::Color(BUTTON_TEXT1_COLOR));
    _text1.setOrigin(_text1.getLocalBounds().width / 2,
                     _text1.getLocalBounds().height / 2);

    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2,
                      _sprite.getGlobalBounds().height / 2);

    _sprite.setScale(0.9, 0.9);
    _text.setScale(0.9, 0.9);
    _text1.setScale(0.9, 0.9);

    _sprite.setPosition(x * BORDER_X, y * BORDER_Y);
    _text.setPosition(x * BORDER_X, y * BORDER_Y);
    _text1.setPosition((x + 0.005) * BORDER_X, (y + 0.005) * BORDER_Y);
}

Title::~Title()
{
}

void Title::display(sf::RenderWindow & window) const
{
    window.draw(_sprite);
    
    window.draw(_text1);
    window.draw(_text);
}

void Title::animate(sf::Event &)
{
    float speed = 0.0005;
    static bool sens = true;
    static sf::Time timeDraw;

    if (_sprite.getScale().x >= 1 && !sens)
    {
        sens = !sens;
        _text.setColor(degradeColor(_text.getColor()));
    }

    if (_sprite.getScale().x <= 0.9 && sens)
    {
        sens = !sens;
    }

    if (sens)
    {
        _sprite.setScale(_sprite.getScale().x - speed * getMs(_time),
                         _sprite.getScale().y - speed * getMs(_time));
        _text.setScale(_text.getScale().x - speed * getMs(_time),
                         _text.getScale().y - speed * getMs(_time));
        _text1.setScale(_text1.getScale().x - speed * getMs(_time),
                         _text1.getScale().y - speed * getMs(_time));
    }
    else
    {
        _sprite.setScale(_sprite.getScale().x + speed * getMs(_time),
                         _sprite.getScale().y + speed * getMs(_time));
        _text.setScale(_text.getScale().x + speed * getMs(_time),
                         _text.getScale().y + speed * getMs(_time));
        _text1.setScale(_text1.getScale().x + speed * getMs(_time),
                         _text1.getScale().y + speed * getMs(_time));
    }
}

void Title::unanimate(sf::Event &)
{
    _text.setColor(sf::Color(BUTTON_TEXT_COLOR));
    _sprite.setScale(0.9, 0.9);
    _text.setScale(0.9, 0.9);
    _text1.setScale(0.9, 0.9);
}

bool Title::isClick(sf::Event & event)
{
    if (Cursor::getPosition().x >= _sprite.getGlobalBounds().left &&
        Cursor::getPosition().x <= _sprite.getGlobalBounds().left + _sprite.getGlobalBounds().width &&
        Cursor::getPosition().y >= _sprite.getGlobalBounds().top &&
        Cursor::getPosition().y <= _sprite.getGlobalBounds().top + _sprite.getGlobalBounds().height)
    {
        if (event.type == sf::Event::MouseButtonReleased
         && event.mouseButton.button == sf::Mouse::Left)
            return true;
    }
    return false;
}

void Title::compute(sf::Event & event)
{
    if (Cursor::getPosition().x >= _sprite.getGlobalBounds().left &&
        Cursor::getPosition().x <= _sprite.getGlobalBounds().left + _sprite.getGlobalBounds().width &&
        Cursor::getPosition().y >= _sprite.getGlobalBounds().top &&
        Cursor::getPosition().y <= _sprite.getGlobalBounds().top + _sprite.getGlobalBounds().height)
    {
        animate(event);
    }
    else
    {
        unanimate(event);
    }
    resetTime(_time);
}