/*
** EPITECH PROJECT, 2020
** Jam.hpp
** File description:
** jam
*/

#pragma once

#include <vector>
#include <list>
#include <string>

namespace Jam
{
    class MainWindow;

    class MainMenu;
    class Game;
    class Pause;

    class Player;
    class Character;
    class AI;

    class Background;
    class BackgroundStar;

    class Camera;
    class Button;
    class Title;

    class Cursor;

    class Factory;
    class AEatable;
    class Eatable;

    enum TextureId
    {
        CURSOR,
        BACKGROUND,
        PLAYER,
        BUTTON,
        TITLE,
        PLANET,
        SPACESHIP,
        BOSS,
        STAR,
        COMET,
        SATELLITE,
        TOTALTEXTURE
    };

    enum FontId
    {
        STARSFIGHTERS,
        TOTALFONT
    };

    enum MusicId
    {
        MAINMENUMUSIC,
        INGAMEMUSIC,
        TOTALMUSIC
    };

    enum Pages
    {
        MAINMENU = 0,
        GAME = 1,
        PAUSE = 2,
        TOTALPAGE = 3
    };

    namespace Constants
    {
        const std::vector<const char *> backgroundPaths =
        {
            "./resources/cursor1.png",
            "./resources/background.png",
            "./resources/Player.png",
            "./resources/baseButton.png",
            "./resources/title.png",
            "./resources/moon_01.png",
            "./resources/satellite_01.png",
            "./resources/boss_01.png",
            "./resources/star_blue01.png",
            "./resources/comet_01.png",
            "./resources/satellite_01.png"
        };
        const std::vector<const char *> fontPaths =
        {
            "./resources/StarsFighters.ttf"
        };
        const std::vector<const char *> musicPaths =
        {
            "./Music/mainmenu.ogg",
            "./Music/ingame.ogg"
        };
    };
}; // namespace Jam

extern Jam::Pages pageId;
