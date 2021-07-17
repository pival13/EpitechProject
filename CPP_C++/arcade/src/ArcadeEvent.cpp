/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019 [WSL: Ubuntu]
** File description:
** ArcadeContent
*/

#include "ArcadeEvent.hpp"

ArcadeEvent::ArcadeEvent(bool pressed, bool released, KeyValue keyValue, int gameId, int displayId)
: _pressed(pressed), _released(released), _keyValue(keyValue), _gameId(gameId), _displayId(displayId)
{}

ArcadeEvent::~ArcadeEvent() {}

bool &ArcadeEvent::isPressed() { return _pressed; }
bool ArcadeEvent::isPressed() const { return _pressed; }
bool &ArcadeEvent::isReleased() { return _released; }
bool ArcadeEvent::isReleased() const { return _released; }
ArcadeEvent::KeyValue &ArcadeEvent::getKeyValue() { return _keyValue; }
ArcadeEvent::KeyValue ArcadeEvent::getKeyValue() const { return _keyValue; }
int &ArcadeEvent::getGameId() { return _gameId; }
int ArcadeEvent::getGameId() const { return _gameId; }
int &ArcadeEvent::getDisplayId() { return _displayId; }
int ArcadeEvent::getDisplayId() const { return _displayId; }
