/*
** EPITECH PROJECT, 2020
** cpp_rush3_2019
** File description:
** Graphic
*/

#ifndef GRAPHIC_HPP_
#define GRAPHIC_HPP_

#include "../Interfaces/IMonitorDisplay.hpp"
#include "ModuleGraph.hpp"
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <iterator>
#include "../Modules/AModuleOneTime.hpp"
#include "../Modules/ModuleDatetime.hpp"
#include "../Modules/ModuleName.hpp"
#include "../Modules/ModuleOSCore.hpp"
#include "../Modules/ModuleCPU.hpp"
#include "../Modules/ModuleMemory.hpp"
#include "GraphicMenu.hpp"
#include "utils.hpp"

class Graphic : public IMonitorDisplay {
    public:
        Graphic();
        ~Graphic();
        void getEvents();
        void setStatus();
        void updateModules();
        bool isEnd() const;
        void drawModules();
        sf::Text stringToText(std::string &);
        sf::RectangleShape *stringToRect(std::string &, int tot);
        void setPosMod();
        void calcY();
        void fillText();
        sf::Font getFont() const {return(_font);};

    private:
        std::vector<ModuleGraph *> _modules;
        int _nbrModGraph = 0;
        int _nbrMod = 0;
        std::map<std::string, bool> _status;
        sf::Color _colorWin = sf::Color(128, 128, 128, 255);
        sf::Vector2i _dimWin = sf::Vector2i(154, 170);
        sf::Vector2i _posWin = sf::Vector2i(1700, 540 - _dimWin.y / 2);
        sf::VideoMode _vm;
        sf::RenderWindow _window;
        sf::Time _delta;
        sf::Event _evt;
        sf::Font _font;
        sf::Texture _textureMod;
        sf::Texture _textureModIn;
        sf::Texture _textureModDate;
};

#endif /* !GRAPHIC_HPP_ */