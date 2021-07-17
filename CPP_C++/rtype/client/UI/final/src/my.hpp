/*
** EPITECH PROJECT, 2020
** JAM_space_2019
** File description:
** my
*/

#ifndef MY_HPP_
#define MY_HPP_

    #include <iostream>
    #include <fstream>
    #include <list>
    #include <vector>
    #include <SFML/Graphics.hpp>
    #include <SFML/Audio.hpp>
    #include <SFML/System.hpp>
    #include <SFML/Window.hpp>
    #include <vector>
    #include <cmath>
    #include <thread>

    #include "Core.hpp"
    #include "communication/include/room.hpp"

class AScene;

typedef enum e_page {
    INTRO,
    MENU ,
    ROOM ,
    GAME,
    END
} page_t;

typedef struct s_game {
    int a;
    page_t actPage;
    page_t nextPage;
    sf::Event event;
    sf::Clock clock;
    sf::Clock parallax;
    sf::RenderWindow window;

    int indexMusic;
    bool popUp;
    bool popDown;
    std::vector<sf::Music *> listMusic;
    sf::Music *music;
    sf::Text *textMusic;
    sf::Font *fontMusic;
    sf::RectangleShape *rectMusic;
    sf::Clock clockMusic;

    AScene *scene;

    Core core;
    std::thread networkThread;
    bool isRunning;
    bool wantRoom;
    bool createRoom;
    bool joinRoom;
    std::string roomUuid;
    std::vector<get_room_t> rooms;
} game_t;

bool mouseInButton(sf::Vector2f pos, const sf::Sprite &sprite);
bool mouseInArea(sf::Vector2f pos, const sf::FloatRect &rect);
bool mouseIsPressed(sf::Event event);
void changeMusic(game_t *gm);

#endif /* !MY_HPP_ */
