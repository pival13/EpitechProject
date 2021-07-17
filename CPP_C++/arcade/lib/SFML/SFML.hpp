/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** sfml
*/

#ifndef SFML_HPP_
#define SFML_HPP_

#include "ADisplayModule.hpp"
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class SFML: public ADisplayModule {
    public:
        SFML(ArcadeContent &pArcadeContent);
        ~SFML();

        void updateEvent() override;
        void setTexture(const std::string &pFilepath) override;
        void display() override;
    private:
        sf::String _name = "Arcade";
        sf::Event _game_event;
        sf::RenderWindow _game_window;
        std::map<std::string, sf::Texture> _texture;
        std::map<char, sf::Sprite> _sprite;
        std::map<char, std::array<size_t, 2>> _anim;
};

extern "C" SFML *getDisplayModule(ArcadeContent &ac);

#endif /* !SFML_DISPLAY_HPP_ */
