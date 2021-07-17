/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019 [WSL: Ubuntu]
** File description:
** Module
*/

#include "Module.hpp"

Module::Module(ArcadeContent &ac)
: arcade(ac)
{
}

Module::~Module()
{
}

size_t Module::getMapWidth() const { return arcade.map.size(); }
size_t Module::getMapHeight() const { return arcade.map[0].size(); }
char Module::getMapAt(int x, int y) const noexcept(false) { return arcade.map.at(x < 0 ? x + getMapWidth() : x).at(y < 0 ? y + getMapHeight() : y); }

bool Module::isKeyUp() const { return arcade.event.getKeyValue() == ArcadeEvent::KeyValue::UP; }
bool Module::isKeyRight() const { return arcade.event.getKeyValue() == ArcadeEvent::KeyValue::RIGHT; }
bool Module::isKeyDown() const { return arcade.event.getKeyValue() == ArcadeEvent::KeyValue::DOWN; }
bool Module::isKeyLeft() const { return arcade.event.getKeyValue() == ArcadeEvent::KeyValue::LEFT; }
bool Module::isKeyEnter() const { return arcade.event.getKeyValue() == ArcadeEvent::KeyValue::ENTER; }
bool Module::isKeyBack() const { return arcade.event.getKeyValue() == ArcadeEvent::KeyValue::ESCAPE; }
bool Module::isKeyPressed() const { return arcade.event.isPressed(); }
bool Module::isKeyReleased() const { return arcade.event.isReleased(); }

void Module::setMapAt(int x, int y, char c) noexcept(false) { arcade.map.at(x < 0 ? x + getMapWidth() : x).at(y < 0 ? y + getMapHeight() : y) = c; }
void Module::cleanMap() { for (std::vector<char> &line : arcade.map) for (char &c : line) c = 0; }

void Module::gameKey(ArcadeEvent::KeyValue key, bool isReleased) { arcade.event.getKeyValue() = key; arcade.event.isReleased() = isReleased; arcade.event.isPressed() = !isReleased; }

void Module::moveUp(bool isReleased) { gameKey(ArcadeEvent::KeyValue::UP, isReleased); }
void Module::moveDown(bool isReleased) { gameKey(ArcadeEvent::KeyValue::DOWN, isReleased); }
void Module::moveRight(bool isReleased) { gameKey(ArcadeEvent::KeyValue::RIGHT, isReleased); }
void Module::moveLeft(bool isReleased) { gameKey(ArcadeEvent::KeyValue::LEFT, isReleased); }
void Module::validate(bool isReleased) { gameKey(ArcadeEvent::KeyValue::ENTER, isReleased); }
void Module::cancel(bool isReleased) { gameKey(ArcadeEvent::KeyValue::ESCAPE, isReleased); }
void Module::backToMenu(bool isReleased) { gameKey(ArcadeEvent::KeyValue::MAINMENU, isReleased); }
void Module::restart(bool isReleased) { gameKey(ArcadeEvent::KeyValue::CHANGE_GAME, isReleased); }
void Module::turnOff(bool isReleased) { gameKey(ArcadeEvent::KeyValue::EXIT, isReleased); }
void Module::nextGame(bool isReleased) { gameKey(ArcadeEvent::KeyValue::CHANGE_GAME, isReleased); arcade.event.getGameId() += 1; }
void Module::prevGame(bool isReleased) { gameKey(ArcadeEvent::KeyValue::CHANGE_GAME, isReleased); arcade.event.getGameId() -= 1; }
void Module::nextGraph(bool isReleased) { gameKey(ArcadeEvent::KeyValue::CHANGE_GRAPH, isReleased); arcade.event.getDisplayId() += 1; }
void Module::prevGraph(bool isReleased) { gameKey(ArcadeEvent::KeyValue::CHANGE_GRAPH, isReleased); arcade.event.getDisplayId() -= 1; }
void Module::releasePressedKey() { arcade.event.isReleased() = true; arcade.event.isPressed() = false; }
void Module::noEvent() { gameKey(ArcadeEvent::KeyValue::NO_KVALUE, true); arcade.event.isReleased() = false; }


void Module::setGame(int game) { arcade.event.getGameId() = game; }
void Module::setGraph(int graph) { arcade.event.getDisplayId() = graph; }
int Module::getGraph() const { return arcade.event.getDisplayId(); }