/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019 [WSL: Ubuntu]
** File description:
** MainMenu
*/

#include "MainMenu.hpp"

MainMenu::MainMenu(ArcadeContent &ac)
: Module(ac), page(0), pos(0), game(0), graph(getGraph())
{
    try {
        gameDirReader.load("games");
        gameDir = gameDirReader.getFiles("lib_arcade_.+.so");
        gameDir.insert(gameDir.begin(), "None");
    } catch (const std::invalid_argument &e) {
        std::cerr << "No directory 'games'" << std::endl;
        gameDir = {"None"};
    }
    graphDirReader.load("lib");
    graphDir = graphDirReader.getFiles("lib_arcade_.+.so");
}

MainMenu::~MainMenu()
{
}

const std::string &MainMenu::getTextureFilepath() const { return path; }

void MainMenu::update()
{
    void (MainMenu::*f[2])() = {&MainMenu::startPage, &MainMenu::enterNickname};
    (this->*f[page])(); 
    if (isKeyEnter() || isKeyBack())
        pos = 0;
    if (page == LAUNCH) {
        setGame(game);
        setGraph(graph);
        restart(true);
    }
}

void MainMenu::startPage()
{
    std::array<const std::string, 7> str = {"Play",
                                "Graphical library",
                                graphDir[graph].substr(11, graphDir[graph].length()-14),
                                "Game",
                                (game == 0 ? gameDir[game] : gameDir[game].substr(11, gameDir[game].length()-14)),
                                "Change a name",
                                "Exit"};

    cleanMap();
    for (size_t i = 0; i != str.size(); i++) {
        for (size_t x = 0; x != str[i].length(); x++)
            setMapAt((getMapWidth()-str[i].length()) / 2 + x, i*2 + (getMapHeight()-str.size()*2+1)/2, str[i].c_str()[x]);
        if (i == pos) {
            setMapAt((getMapWidth()-str[i].length()) / 2 - 2, i*2 + (getMapHeight()-str.size()*2+1)/2, '>');
            setMapAt((getMapWidth()-str[i].length()) / 2 + str[i].length() + 1, i*2 + (getMapHeight()-str.size()*2+1)/2, '<');
        }
    }
    if (isKeyUp())
        pos = (pos == 2 ? 0 : (pos == 4 ? 2 : (pos + str.size()-1) % str.size()));
    else if (isKeyDown())
        pos = (pos == 0 ? 2 : (pos == 2 ? 4 : (pos + 1) % str.size()));
    else if (isKeyEnter()) {
        if (pos == 0 && game != 0) page = LAUNCH;
        else if (pos == 2) pos = 4;
        else if (pos == 4) pos = 5;
        else if (pos == 5) page = ENTER_NAME;
        else if (pos == 6) turnOff(true);
    } else if (isKeyBack())
        pos = 6;
    else if (isKeyRight()) {
        if (pos == 2) graph = (graph == graphDir.size()-1 ? 0 : graph+1);
        else if (pos == 4 && gameDir.size() != 1) game = (game == gameDir.size()-1 ? 1 : game+1);
    } else if (isKeyLeft()) {
        if (pos == 2) graph = (graph == 0 ? graphDir.size()-1 : graph-1);
        else if (pos == 4 && gameDir.size() != 1) game = (game == 1 ? gameDir.size()-1 : (game+gameDir.size()-1) % gameDir.size());
    }
}

void MainMenu::enterNickname()
{
    const std::string str = "Back";
    cleanMap();
    for (size_t x = 0; x != str.length(); x++)
        setMapAt((getMapWidth()-str.length()) / 2 + x, getMapHeight()/2, str.c_str()[x]);
    setMapAt((getMapWidth()-str.length()) / 2 - 2, getMapHeight()/2, '>');
    setMapAt((getMapWidth()-str.length()) / 2 + str.length() + 1, getMapHeight()/2, '<');
    if (isKeyEnter())
        page = START;
}

MainMenu *getGameModule(ArcadeContent &ac)
{
    return new MainMenu(ac);
}