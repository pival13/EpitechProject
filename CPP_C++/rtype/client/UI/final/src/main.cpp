/*
** EPITECH PROJECT, 2020
** JAM_space_2019
** File description:
** main
*/

#include "my.hpp"
#include "Intro.hpp"
#include "Menu.hpp"
#include "End.hpp"
#include "Game.hpp"
#include "SFML/Graphics.hpp"

void changeMusic(game_t *gm)
{
    float volume = gm->music->getVolume();

    if (gm->indexMusic < 8) gm->indexMusic++;
    else gm->indexMusic = 0;
    gm->music->pause();
    gm->music = gm->listMusic.at(gm->indexMusic);
    gm->music->play();
    gm->music->setVolume(volume);
    gm->popUp = false;
    gm->popDown = true;
}

void actualizePage(game_t *gm, sf::RenderWindow *window)
{
    if (gm->nextPage == INTRO && gm->nextPage != gm->actPage) {
        delete(gm->scene);
        gm->scene = new Intro();
    } else if (gm->nextPage == MENU && gm->nextPage != gm->actPage) {
        delete(gm->scene);
        gm->clock.restart();
        gm->scene = new Menu();
        gm->a = 1;
    } else if (gm->nextPage == END && gm->nextPage != gm->actPage) {
         delete(gm->scene);
         gm->clock.restart();
         gm->scene = new End();
         gm->isRunning = false;
    } else if (gm->nextPage == GAME && gm->nextPage != gm->actPage) {
        delete(gm->scene);
        gm->clock.restart();
        gm->scene = new ClientGame();
    }
    gm->actPage = gm->nextPage;
    if (gm->indexMusic == 0)  gm->textMusic->setString("Menu");
    else if (gm->indexMusic == 1) gm->textMusic->setString("Syringe");
    else if (gm->indexMusic == 2) gm->textMusic->setString("137");
    else if (gm->indexMusic == 3) gm->textMusic->setString("Olografiks");
    else if (gm->indexMusic == 4) gm->textMusic->setString("Asidrift");
    else if (gm->indexMusic == 5) gm->textMusic->setString("Midrift");
    else if (gm->indexMusic == 6) gm->textMusic->setString("Driftever");
    else if (gm->indexMusic == 7) gm->textMusic->setString("Klem");
    else if (gm->indexMusic == 8) gm->textMusic->setString("Rtype");
    
    if (gm->popDown) {
        if (gm->clockMusic.getElapsedTime().asMilliseconds() > 0.1 && gm->rectMusic->getPosition().y < 30) {
            gm->rectMusic->setPosition(gm->rectMusic->getPosition().x, gm->rectMusic->getPosition().y + 2);
            gm->clockMusic.restart();
        } else if (gm->rectMusic->getPosition().y == 30) {
            if (gm->clockMusic.getElapsedTime().asMilliseconds() > 1000) {
                gm->popDown = false;
                gm->popUp = true;
            }
        }
    } else if (gm->popUp) {
        if (gm->clockMusic.getElapsedTime().asMilliseconds() > 0.1 && gm->rectMusic->getPosition().y > -210) {
            gm->rectMusic->setPosition(gm->rectMusic->getPosition().x, gm->rectMusic->getPosition().y - 2);
            gm->clockMusic.restart();
        } else if (gm->rectMusic->getPosition().y == -210) {
            gm->popUp = false;
        }
    }
    gm->textMusic->setPosition(750, gm->rectMusic->getPosition().y + 12);
    gm->scene->updateGame(gm, window);
    gm->scene->drawGame(gm, window);
    window->draw(*gm->rectMusic);
    window->draw(*gm->textMusic);
    window->display();
}

void gameEvents(game_t *gm, sf::RenderWindow *window)
{
    gm->scene->getEvents(gm, window);
}

void globalEvents(game_t *gm, sf::RenderWindow *window)
{
    if (gm->event.type == sf::Event::Closed)
        window->close();
    if (gm->event.type == sf::Event::KeyPressed) {
        if (gm->event.key.code == sf::Keyboard::P) {
            if (gm->music->getStatus() == sf::Music::Status::Playing) gm->music->pause();
            else if (gm->music->getStatus() == sf::Music::Status::Paused) gm->music->play();
        }
        if (gm->event.key.code == sf::Keyboard::A) changeMusic(gm);
    }
}

void loadMusic(game_t *game)
{
    std::string dir = __FILE__;
    dir = dir.substr(0, dir.find_last_of("\\/"));
    sf::Music *music = new sf::Music();
    music->openFromFile(dir + "/../../Musics/Gamemenu.ogg");
    game->listMusic.push_back(music);
    sf::Music *music1 = new sf::Music();
    music1->openFromFile(dir + "/../../Musics/Syringe.ogg");
    game->listMusic.push_back(music1);
    sf::Music *music2 = new sf::Music();
    music2->openFromFile(dir + "/../../Musics/Trap137.ogg");
    game->listMusic.push_back(music2);
    sf::Music *music3 = new sf::Music();
    music3->openFromFile(dir + "/../../Musics/Trumpet.ogg");
    game->listMusic.push_back(music3);
    sf::Music *music4 = new sf::Music();
    music4->openFromFile(dir + "/../../Musics/asiantrapbeat.ogg");
    game->listMusic.push_back(music4);
    sf::Music *music5 = new sf::Music();
    music5->openFromFile(dir + "/../../Musics/damsohardtrapbeat.ogg");
    game->listMusic.push_back(music5);
    sf::Music *music6 = new sf::Music();
    music6->openFromFile(dir + "/../../Musics/indietrap.ogg");
    game->listMusic.push_back(music6);
    sf::Music *music7 = new sf::Music();
    music7->openFromFile(dir + "/../../Musics/klem.ogg");
    game->listMusic.push_back(music7);
    sf::Music *music8 = new sf::Music();
    music8->openFromFile(dir + "/../../Musics/testmp3.ogg");
    game->listMusic.push_back(music8);
}

void threadTCP(game_t &game)
{
    game.core.initConnection();
    while (game.isRunning) {
        if (!game.core.isRunning()) {
            game.core.initConnection();
        } else {
            if (game.wantRoom) {
                if (game.core.setRooms()) {
                    game.rooms = game.core.getRooms();
                    game.wantRoom = false;
                }
            }

            if (game.createRoom) {
                if (game.core.createRoom("My room", 4, 0, 1)) {
                    game.roomUuid = game.core.getRoomUuid();
                    game.nextPage = GAME;
                    game.createRoom = false;
                    game.joinRoom = false;
                    game.wantRoom = false;
                }
            }

            if (game.joinRoom && !game.roomUuid.empty()) {
                if (game.core.joinRoom(game.roomUuid.data())) {
                    game.nextPage = GAME;
                    game.joinRoom = false;
                    game.createRoom = false;
                    game.wantRoom = false;
                }
            } else if (!game.joinRoom)
                game.joinRoom = false;
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void initialiseAll(game_t *game)
{
    std::string dir = __FILE__;
    dir = dir.substr(0, dir.find_last_of("\\/"));

    game->scene = new Intro();
    game->nextPage = INTRO;
    game->actPage = game->nextPage;
    game->clock = sf::Clock();
    game->event = sf::Event();

    game->indexMusic = 0;
    loadMusic(game);
    game->music = game->listMusic.at(game->indexMusic);
    game->music->setVolume(25);
    game->popUp = false;
    game->popDown = false;
    game->fontMusic = new sf::Font();
    game->fontMusic->loadFromFile(dir + "/../font/In your face, joffrey!.ttf");
    game->rectMusic = new sf::RectangleShape(sf::Vector2f(500, 100));
    game->rectMusic->setFillColor(sf::Color(172, 169, 169, 40));
    game->rectMusic->setPosition(1920 / 2 - 500 / 2, -210);
    game->rectMusic->setOutlineThickness(3.0f);
    game->rectMusic->setOutlineColor(sf::Color::Black);
    game->textMusic = new sf::Text("", *game->fontMusic, 65);
    game->textMusic->setFillColor(sf::Color::White);
    game->textMusic->setPosition(750 , game->rectMusic->getPosition().y + 40);

    game->isRunning = true;
    game->wantRoom = false;
    game->createRoom = false;
    game->joinRoom = false;

    game->networkThread = std::thread([game]() { threadTCP(*game); });
}

void loopGame()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Proto-Type V2.1.01", sf::Style::Default);
    game_t gm;
    
    initialiseAll(&gm);
    window.setFramerateLimit(60);
    sf::Image img;
    img.loadFromFile(std::string(__FILE__).substr(0, std::string(__FILE__).find_last_of("\\/")) + "/../img_src/icon.png");
    window.setIcon(img.getSize().x, img.getSize().y, img.getPixelsPtr());
    gm.music->play();
    try {
        while (window.isOpen()) {
            if (gm.music->getStatus() == sf::Music::Stopped) changeMusic(&gm);
            while (window.pollEvent(gm.event)) {
                globalEvents(&gm, &window);
                gameEvents(&gm, &window);
            }
            actualizePage(&gm, &window);
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    delete(gm.fontMusic);
    for (auto music : gm.listMusic) delete(music);
    delete(gm.scene);
    gm.isRunning = false;
    gm.networkThread.join();
}

#include "AnimatedSprite.hpp"
class A : public AnimatedSprite
{
    public:
    A() : AnimatedSprite(10, {
        {"test", AnimatedSprite::AnimatedSpriteData(
            std::string(__FILE__).substr(0, std::string(__FILE__).find_last_of("\\/")) + "/../img_src/explode.png",
            Transform({-15, 0, 0}, {70, 65, 0}), {70+134, 0}, 7
            //std::string(__FILE__).substr(0, std::string(__FILE__).find_last_of("\\/")) + "/../img_src/AED.png",
            //Transform({0, 0, 0}, {150, 102, 0}), {150, 0}, 9
            //std::string(__FILE__).substr(0, std::string(__FILE__).find_last_of("\\/")) + "/../img_src/dieplayer.png",
            //Transform({0, 0, 0}, {164, 327, 0}, {0.5, 0.5, 0.5}, {0, 0, 90}), {164+41, 0}, 13
            //std::string(__FILE__).substr(0, std::string(__FILE__).find_last_of("\\/")) + "/../img_src/PED.png",
            //Transform({-20, 0, 0}, {288, 255, 0}), {288, 0}, 12
        )}
    }) {}
    ~A() {}
};

int main(int , char **)
{
    loopGame();
    return 0;
}