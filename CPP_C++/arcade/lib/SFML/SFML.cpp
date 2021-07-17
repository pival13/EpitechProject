/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** sfml
*/

#include "SFML.hpp"

SFML::SFML(ArcadeContent &pArcadeContent) : ADisplayModule(pArcadeContent)
{
    sf::Vector2u vector(1600, 960);
    _game_window.create(sf::VideoMode(1600, 960), _name);
}

SFML::~SFML()
{
    _game_window.close();
}

void SFML::updateEvent()
{
    while (_game_window.pollEvent(_game_event)) {
        if (_game_event.type == sf::Event::Closed)
            turnOff();
        else if (_game_event.type == sf::Event::KeyPressed) {
            if (_game_event.key.code == sf::Keyboard::X)
                turnOff();
            else if (_game_event.key.code == sf::Keyboard::Z || _game_event.key.code == sf::Keyboard::Up)
                moveUp();
            else if (_game_event.key.code == sf::Keyboard::Q || _game_event.key.code == sf::Keyboard::Left)
                moveLeft();
            else if (_game_event.key.code == sf::Keyboard::S || _game_event.key.code == sf::Keyboard::Down)
                moveDown();
            else if (_game_event.key.code == sf::Keyboard::D || _game_event.key.code == sf::Keyboard::Right)
                moveRight();
            else if (_game_event.key.code == sf::Keyboard::Space)
                validate();
            else if (_game_event.key.code == sf::Keyboard::B)
                cancel();
            else if (_game_event.key.code == sf::Keyboard::R)
                restart();
            else if (_game_event.key.code == sf::Keyboard::P)
                backToMenu();
            else if (_game_event.key.code == sf::Keyboard::Num1)
                prevGraph();
            else if (_game_event.key.code == sf::Keyboard::Num2)
                nextGraph();
            else if (_game_event.key.code == sf::Keyboard::Num3)
                prevGame();
            else if (_game_event.key.code == sf::Keyboard::Num4)
                nextGame();
            else
                releasePressedKey();
        } else if (_game_event.type == sf::Event::KeyReleased)
            noEvent();
    }
}

void SFML::setTexture(const std::string &pFilepath)
{
    ParserArcadeFileTexture parser(pFilepath);
    std::vector<char> lChar = parser.getSymbols();

    _sprite.clear();
    _anim.clear();
    for (char character : lChar)
    {
        std::string textureName = parser.getFilePath(character);
        if (!_texture.count(textureName)) {
            sf::Texture text;
            text.loadFromFile(textureName);
            _texture.insert(std::pair<std::string, sf::Texture>(textureName, text));
        }
        auto rect = parser.getTextureRect(character);
        sf::Sprite sprite(_texture[textureName], sf::IntRect(rect[0], rect[1], rect[2], rect[3]));
        sprite.setScale((float)32 / rect[2], (float)32 / rect[3]);
        _sprite.insert(std::pair<char, sf::Sprite>(character, sprite));
        _anim.insert(std::pair<char, std::array<size_t, 2>>(character, {0,rect[4]}));
    }
}

void SFML::display()
{
    static int anim = 0;
    if (anim == 3) {
        for (auto a : _anim) {
            sf::IntRect rect = _sprite[a.first].getTextureRect();
            rect.left -= rect.width * _anim[a.first][0];
            if (_anim[a.first][1] != 0)
                _anim[a.first] = {(_anim[a.first][0]+1) % _anim[a.first][1], _anim[a.first][1]};
            rect.left += rect.width * _anim[a.first][0];
            _sprite[a.first].setTextureRect(rect);
        }
        anim = 0;
    } else
        anim++;

    _game_window.clear();
    for (size_t y = 0; y != getMapHeight(); y++) {
        for (size_t x = 0; x != getMapWidth(); x++) {
            _sprite[getMapAt(x, y)].setPosition(x*32, y*32);
            _game_window.draw(_sprite[getMapAt(x, y)]);
        }
    }
    _game_window.display();
}

SFML *getDisplayModule(ArcadeContent &ac)
{
    return new SFML(ac);
}