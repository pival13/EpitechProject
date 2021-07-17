/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019 [WSL: Ubuntu]
** File description:
** ArcadeEvent
*/

class ArcadeEvent
{
    public:
        enum KeyValue
        {
            NO_KVALUE = -1,
            LEFT, RIGHT, UP, DOWN,
            ESCAPE, ENTER,
            EXIT, MAINMENU,
            CHANGE_GAME, CHANGE_GRAPH
        };

    public:
        ArcadeEvent(bool pressed = false, bool released = false,
                    KeyValue keyValue = KeyValue::NO_KVALUE,
                    int gameId = 0,
                    int displayId = 0);
        ~ArcadeEvent();

        bool &isPressed();
        bool &isReleased();
        KeyValue &getKeyValue();
        int &getGameId();
        int &getDisplayId();
        bool isPressed() const;
        bool isReleased() const;
        KeyValue getKeyValue() const;
        int getGameId() const;
        int getDisplayId() const;

    private:
        bool _pressed = false;
        bool _released = false;
        KeyValue _keyValue = KeyValue::NO_KVALUE;
        int _gameId = 0;
        int _displayId = 0;
};

#include <vector>

class ArcadeContent
{
public:
    ArcadeContent() = default;
    ~ArcadeContent() = default;

    std::vector<std::vector<char>> map;
    ArcadeEvent event;
};

/*
mapChar filepathToSpritesheet x y width height nbAnim usedChar*2 textColor backgroundColor

~ ./game/qix/sprite/terrain.png 35 60 20 20 1 -- 2 0
# ./game/qix/sprite/terrain.png 35 60 20 20 1 ** 2 0
| ./game/qix/sprite/terrain.png 35 60 20 20 1 || 2 0
a ./game/qix/sprite/player.png 35 60 20 20 1 {} 2 0
A ./game/qix/sprite/player.png 55 60 20 20 1 {} 3 0

~~~~~~~~~~~~~~~~~~~~~~~~        ------------------------
| a    A           *   |    \   ||  {}       {}           *   |
|               *      |  -- \  ||                     *      |
|    *     *           |  -- /  ||          *     *           |
|                      |    /   ||                            |
~~~~~~~~~~~~~~~~~~~~~~~~        ------------------------
*/
