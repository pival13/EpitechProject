/*
** EPITECH PROJECT, 2020
** MainWindow.cpp
** File description:
** main window
*/

#include "MainWindow.hpp"

#include "Player.hpp"

using namespace Jam;
using namespace sf;

Pages pageId = MAINMENU;

VideoMode DesktopMode = VideoMode::getDesktopMode();

MainWindow::MainWindow(int argc, const char * const * argv)
    : _argc { argc }
    , _argv { argv }
    , _window(DesktopMode,
              "xXx_JAM_Space_Game_Of_The_Dead_xXx",
              sf::Style::Titlebar | sf::Style::Close | sf::Style::Fullscreen)
    , _background ({(unsigned int)BORDER_X, (unsigned int)BORDER_Y})
{
    _musics.push_back(std::unique_ptr<sf::Music>(new sf::Music()));
    _musics.push_back(std::unique_ptr<sf::Music>(new sf::Music()));

    _musics[0]->openFromFile(Constants::musicPaths[MAINMENU]);
    _musics[0]->setVolume(30);

    _musics[1]->openFromFile(Constants::musicPaths[MusicId::INGAMEMUSIC]);
    _musics[1]->setVolume(30);
}

MainWindow::~MainWindow()
{
}

void MainWindow::playMusic()
{
    static MusicId musicId = MusicId::MAINMENUMUSIC;

    if (pageId == Pages::MAINMENU)
        musicId = MusicId::MAINMENUMUSIC;
    else if (pageId == Pages::GAME)
        musicId = MusicId::INGAMEMUSIC;
    else if (pageId == Pages::PAUSE)
        musicId = MusicId::INGAMEMUSIC;

    for (unsigned char i = MusicId::MAINMENUMUSIC; i != MusicId::TOTALMUSIC; ++i)
    {
        if (i != musicId)
            _musics[i]->stop();
    }

    if (_musics[musicId]->getStatus() != sf::Music::Playing)
        _musics[musicId]->play();
}

int MainWindow::exec()
{
    Pages actualPage = Pages::MAINMENU;

    if (create() == EXIT_FAILURE)
        return EXIT_FAILURE;

    // Filling pages.
    _pages.push_back(std::unique_ptr<IPage>(new MainMenu));
    _pages.push_back(std::unique_ptr<IPage>(new Game));
    _pages.push_back(std::unique_ptr<IPage>(new Pause));

    _window.setMouseCursorVisible(false);

    while (_window.isOpen())
    {
        if (_window.pollEvent(_event))
            if (_event.type == sf::Event::Closed)
                _window.close();
        _window.clear(sf::Color(0x070612ff));

        _background.printStars(_window);

        _pages[pageId]->execute(_window, _event);

        if (actualPage != pageId)
            _pages[pageId]->executeChangePage(_window, _event);

        _cursor.execute(_window, _event);
        playMusic();

        _background.move(_window.getView().getCenter());

        _window.display();

        actualPage = pageId;
    }
    return EXIT_SUCCESS;
}

int MainWindow::create()
{
    // Sprites
    _sprites.push_back(newSprite(textureBase[TextureId::BACKGROUND]));
    return EXIT_SUCCESS;
}