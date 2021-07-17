/*
** EPITECH PROJECT, 2020
** RType_2020
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#include "AScene.hpp"

class Menu : public AScene
{
    public:
        Menu();
        ~Menu();

        void drawRooms(game_t *, sf::RenderWindow *);
        void drawGame(game_t *, sf::RenderWindow *);
        void updateGame(game_t *, sf::RenderWindow *);
        void getEvents(game_t *, sf::RenderWindow *);
    private:
        sf::Time _time;
        sf::Sprite _bg;
        sf::Sprite _bgCpy;
        sf::Sprite *_title;

        bool _isScaling;
        bool _isSettings;
        bool _isRoom;
        sf::Vector2f _titleSize;
        int _nbr;
        bool _inPlay;
        bool _inExit;
        bool _inOptions;
        bool _inCross;
        bool _inPlus;
        bool _inMoins;
        bool _inEdit;
        bool _inCreate;
        bool _inJoin;
        bool _inNameRoom;

        sf::Sprite _buttonCross;
        sf::Sprite _buttonCrossIn;
        sf::Sprite _settingBlurForm;
        sf::Sprite _RoomCadre;
        sf::Sprite _volume;
        sf::Sprite _buttonMoins;
        sf::Sprite _buttonPlus;
        sf::Sprite _buttonMoinsIn;
        sf::Sprite _buttonPlusIn;

        sf::Sprite _buttonPlay;
        sf::Sprite _buttonPlayIn;
        sf::Sprite _buttonExit;
        sf::Sprite _buttonExitIn;
        sf::Sprite _buttonOptions;
        sf::Sprite _buttonOptionsIn;
        sf::Sprite _buttonEdit;
        sf::Sprite _buttonEditIn;
        sf::Sprite _blurform;
        sf::Sprite _buttonCreateIn;
        sf::Sprite _buttonCreate;
        sf::Sprite _buttonJoin;
        sf::Sprite _buttonJoinIn;
        sf::Sprite _buttonNameRoom;
        sf::Sprite _buttonNameRoomIn;
        sf::Sprite _buttonNameRoomClick;
        sf::Sprite _buttonNameRoomIndisp;
};

#endif /* !MENU_HPP_ */
