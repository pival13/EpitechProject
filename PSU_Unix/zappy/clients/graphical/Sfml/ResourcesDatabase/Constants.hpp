/*
** By Kevin Pruvost, May 2020
** Constants.hpp
** File description:
** cst
*/

#pragma once

// Project includes
#include "KVector.hpp"

// C++ includes
#include <tuple>

/**
 * @brief Where every important constants are.
 */
namespace Constants
{
    constexpr const auto resourcesPath = "resources/";
    constexpr const auto spritesPath = "resources/sprites/";
    constexpr const auto musicsPath = "resources/sounds/";
    constexpr const auto fontsPath = "resources/fonts/";

    const KVector<std::tuple<std::string, size_t, size_t>> spritesPaths = {
        {"Menu/Menu_Preview.png", 3, 1},
        {"Game/mobs/zergling.png", 5, 2},
        {"Game/mobs/ultralisk.png", 5, 2},
        {"Game/mobs/cocoon.png", 5, 3},
        {"Game/mobs/queen.png", 5, 2},
        {"Game/mobs/larva.png", 5, 2},
        {"Game/mobs/drone.png", 5, 2},
        {"Game/mobs/hydralisk.png", 5, 2},
        {"Game/mobs/baneling.png", 5, 2},
        {"Game/mobs/roach.png", 5, 2},
        {"Game/floor/floor1.png", 1, 1},
        {"Game/floor/floor2.png", 1, 1},
        {"Game/minerals/blue.png", 1, 1},
        {"Game/minerals/green.png", 1, 1},
        {"Game/minerals/orange.png", 1, 1},
        {"Game/minerals/purple.png", 1, 1},
        {"Game/minerals/red.png", 1, 1},
        {"Game/minerals/yellow.png", 1, 1},
        {"Game/background/sky.png", 1, 1},
        {"cursor.png", 5, 2},
        {"Game/minerals/food.png", 1, 1},
        {"Game/interface/descPanel.png", 1, 1},
        {"Game/interface/overlay.png", 1, 1},
        {"Game/interface/tvEffect.png", 10, 1},
        {"Game/interface/tvBackground.png", 1, 1},
        {"Game/interface/faces/egg.png", 1, 1},
        {"Game/interface/faces/larva.png", 1, 1},
        {"Game/interface/faces/drone.png", 1, 1},
        {"Game/interface/faces/zergling.png", 1, 1},
        {"Game/interface/faces/baneling.png", 1, 1},
        {"Game/interface/faces/roach.png", 1, 1},
        {"Game/interface/faces/hydralisk.png", 1, 1},
        {"Game/interface/faces/queen.png", 1, 1},
        {"Game/interface/faces/ultralisk.png", 1, 1},
        {"Game/interface/faces/floor.png", 1, 1},
        {"Game/interface/compass.png", 1, 4},
        {"Game/interface/compassCursor.png", 1, 1},
        {"Game/interface/timePanel.png", 1, 1},
        {"Game/interface/timeSetButton.png", 1, 1},
        {"Game/interface/timeTextSpace.png", 1, 1},
        {"Game/interface/bottomBar/arrowLeft.png", 1, 1},
        {"Game/interface/bottomBar/arrowRight.png", 1, 1},
        {"Game/interface/bottomBar/arrowDown.png", 1, 1},
        {"Game/interface/bottomBar/arrowUp.png", 1, 1},
        {"Game/interface/bottomBar/playersButton.png", 1, 1},
        {"Game/interface/bottomBar/teamsButton.png", 1, 1},
        {"Game/interface/bottomBar/playerSquare.png", 1, 1},
        {"Game/interface/bottomBar/teamSquare.png", 1, 1},
        {"Menu/background.png", 1, 1},
        {"Menu/buttons/vert_push_play.png", 1, 1},
        {"Menu/buttons/vert_push_quit.png", 1, 1},
        {"Menu/planet.png", 1, 1},
        {"Menu/title.png", 1, 1}
    };

    const KVector<std::string> musicsPaths = {
        "music.ogg",
        "cocoon.ogg",
        "larva.ogg",
        "drone.ogg",
        "zergling.ogg",
        "baneling.ogg",
        "roach.ogg",
        "hydralisk.ogg",
        "queen.ogg",
        "ultralisk.ogg"
    };

    const KVector<std::string> fontsPaths = {
        "Starcraft.ttf"
    };

    enum TextureId
    {
        BACKGROUND,
        ZERGLING,
        ULTRALISK,
        COCOON,
        QUEEN,
        LARVA,
        DRONE,
        HYDRALISK,
        BANELING,
        ROACH,
        FLOOR1,
        FLOOR2,
        LINEMATE_TEXTURE,
        DERAUMERE_TEXTURE,
        SIBUR_TEXTURE,
        MENDIANE_TEXTURE,
        PHIRAS_TEXTURE,
        THYSTAME_TEXTURE,
        SKY_BACKGROUND,
        CURSOR,
        FOOD,
        DESC_PANEL,
        GAME_OVERLAY,
        TV_EFFECT,
        TV_BACKGROUND,
        FACE_COCOON,
        FACE_LARVA,
        FACE_DRONE,
        FACE_ZERGLING,
        FACE_BANELING,
        FACE_ROACH,
        FACE_HYDRALISK,
        FACE_QUEEN,
        FACE_ULTRALISK,
        FACE_FLOOR,
        COMPASS,
        COMPASS_CURSOR,
        TIME_PANEL,
        TIME_SET_BUTTON,
        TIME_TEXT_SPACE,
        BOTTOM_ARROW_LEFT,
        BOTTOM_ARROW_RIGHT,
        BOTTOM_ARROW_DOWN,
        BOTTOM_ARROW_UP,
        BOTTOM_PLAYERS_BUTTON,
        BOTTOM_TEAMS_BUTTON,
        BOTTOM_PLAYER_SQUARE,
        BOTTOM_TEAMS_SQUARE,
        MENU_BACKGROUND,
        MENU_PLAY,
        MENU_QUIT,
        MENU_PLANET,
        MENU_TITLE,
        TOTAL_TEXTURE
    };
    enum MusicId
    {
        MUSIC_GAME,
        SOUND_COCOON,
        SOUND_LARVA,
        SOUND_DRONE,
        SOUND_ZERGLING,
        SOUND_BANELING,
        SOUND_ROACH,
        SOUND_HYDRALISK,
        SOUND_QUEEN,
        SOUND_ULTRALISK,
        TOTAL_SOUND
    };
    enum FontId
    {
        STARCRAFT_FONT,
        TOTAL_FONT
    };
}; // !Constants