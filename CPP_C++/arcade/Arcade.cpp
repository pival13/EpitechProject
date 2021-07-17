/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019 [WSL: Ubuntu]
** File description:
** Arcade
*/

#include "Arcade.hpp"

/************************************/
/*              Arcade              */
/************************************/

Arcade::Arcade(const std::string &graphPath, const std::string &gamePath) noexcept(false)
: _isPowerUp(true)
{
    interface.map.resize(50);
    for (std::vector<char> &line : interface.map) {
        line.resize(30);
        std::fill(line.begin(), line.end(), ' ');
    }
    try {
        DirReader dir("lib");
        std::vector<std::string> files = dir.getFiles("lib_arcade_.+.so");
        for (int i = 0; i != (int)files.size(); i++)
            if (!strcasecmp(files[i].c_str(), graphPath.substr(graphPath.find_last_of("/")+1).c_str()))
                interface.event.getDisplayId() = i;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    loadGame(gamePath);
    loadGraph(graphPath);
    _currentGraph = interface.event.getDisplayId();
}

Arcade::~Arcade()
{
}

void Arcade::loadGame(const std::string &gamePath) noexcept(false)
{
    game.reset();
    gameLib.load(gamePath);
    game.reset(gameLib.getFunction<IGameModule *(ArcadeContent &)>("getGameModule")(interface));
}

void Arcade::loadGraph(const std::string &displayPath) noexcept(false)
{
    graph.reset();
    graphLib.load(displayPath);
    auto f = graphLib.getFunction<IDisplayModule *(ArcadeContent &)>("getDisplayModule");
    auto ptr = f(interface);
    graph.reset(ptr);
    if (game)
        graph->setTexture(game->getTextureFilepath());
}

void Arcade::changeGame()
{
    try {
        DirReader dir("games");
        std::vector<std::string> files = dir.getFiles("lib_arcade_.+.so");
        for (std::string &f : files)
            f = "games/" + f;
        files.insert(files.begin(), "./lib_arcade_MainMenu.so");
        
        if (interface.event.getKeyValue() == interface.event.MAINMENU || files.size() == 1)
            interface.event.getGameId() = 0;
        else {
            while (interface.event.getGameId() >= (int)files.size())
                interface.event.getGameId() -= (int)files.size() - 1;
            while (interface.event.getGameId() <= 0)
                interface.event.getGameId() += (int)files.size() - 1;
        }

        loadGame(files[interface.event.getGameId()]);
    } catch (const std::invalid_argument &e) {
        std::cerr << e.what() << std::endl;
        loadGame("./lib_arcade_MainMenu.so");
    }
    changeGraph();
}

void Arcade::changeGraph()
{
    if (_currentGraph == interface.event.getDisplayId()) {
        if (game)
            graph->setTexture(game->getTextureFilepath());
        return;
    }
    try {
        DirReader dir("lib");
        std::vector<std::string> files = dir.getFiles("lib_arcade_.+.so");
        for (std::string &f : files)
            f = "lib/" + f;
        
        if (files.size() == 0)
            throw std::runtime_error("No graphical library at 'lib/'");

        while (interface.event.getDisplayId() >= (int)files.size())
            interface.event.getDisplayId() -= (int)files.size();
        while (interface.event.getDisplayId() < 0)
            interface.event.getDisplayId() += (int)files.size();

        loadGraph(files[interface.event.getDisplayId()]);
        _currentGraph = interface.event.getDisplayId();
    } catch (const std::logic_error &e) {
        std::cerr << e.what() << std::endl;
    }
}

void Arcade::checkInput()
{
    if (interface.event.getKeyValue() == interface.event.EXIT)
        _isPowerUp = false;
    if (interface.event.getKeyValue() == interface.event.CHANGE_GAME || interface.event.getKeyValue() == interface.event.MAINMENU)
        changeGame();
    if (interface.event.getKeyValue() == interface.event.CHANGE_GRAPH)
        changeGraph();
}

void Arcade::play()
{
    std::chrono::milliseconds t(std::chrono::system_clock::now().time_since_epoch().count() / 1000000);

    while (_isPowerUp) {
        graph->updateEvent();
        try {
            game->update();
        } catch(const std::exception &e) {
            std::cerr << e.what() << std::endl;
            loadGame("./lib_arcade_MainMenu.so");
            graph->setTexture(game->getTextureFilepath());
        }
        graph->display();
        //t += std::chrono::milliseconds(1000/15);
        checkInput();
        interface.event.getKeyValue() = interface.event.NO_KVALUE;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000/15));
    }
}