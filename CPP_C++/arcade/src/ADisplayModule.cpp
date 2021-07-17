/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019 [WSL: Ubuntu]
** File description:
** ADisplayModule
*/

#include "ADisplayModule.hpp"

ADisplayModule::ADisplayModule(ArcadeContent &ac)
: Module(ac)
{
}

char ADisplayModule::getMapAt(int x, int y) const noexcept(false) { return Module::getMapAt(x, y); }
size_t ADisplayModule::getMapWidth() const { return Module::getMapWidth(); }
size_t ADisplayModule::getMapHeight() const { return Module::getMapHeight(); }

bool ADisplayModule::isKeyUp() const { return Module::isKeyUp(); }
bool ADisplayModule::isKeyRight() const { return Module::isKeyRight(); }
bool ADisplayModule::isKeyDown() const { return Module::isKeyDown(); }
bool ADisplayModule::isKeyLeft() const { return Module::isKeyLeft(); }
bool ADisplayModule::isKeyEnter() const { return Module::isKeyEnter(); }
bool ADisplayModule::isKeyBack() const { return Module::isKeyBack(); }
bool ADisplayModule::isKeyPressed() const { return Module::isKeyPressed(); }
bool ADisplayModule::isKeyReleased() const { return Module::isKeyReleased(); }

void ADisplayModule::moveUp(bool isReleased) { Module::moveUp(isReleased); }
void ADisplayModule::moveDown(bool isReleased) { Module::moveDown(isReleased); }
void ADisplayModule::moveRight(bool isReleased) { Module::moveRight(isReleased); }
void ADisplayModule::moveLeft(bool isReleased) { Module::moveLeft(isReleased); }
void ADisplayModule::validate(bool isReleased) { Module::validate(isReleased); }
void ADisplayModule::cancel(bool isReleased) { Module::cancel(isReleased); }
void ADisplayModule::backToMenu(bool isReleased) { Module::backToMenu(isReleased); }
void ADisplayModule::restart(bool isReleased) { Module::restart(isReleased); }
void ADisplayModule::turnOff(bool isReleased) { Module::turnOff(isReleased); }
void ADisplayModule::nextGame(bool isReleased) { Module::nextGame(isReleased); }
void ADisplayModule::prevGame(bool isReleased) { Module::prevGame(isReleased); }
void ADisplayModule::nextGraph(bool isReleased) { Module::nextGraph(isReleased); }
void ADisplayModule::prevGraph(bool isReleased) { Module::prevGraph(isReleased); }
void ADisplayModule::releasePressedKey() { Module::releasePressedKey(); }
void ADisplayModule::noEvent() { Module::noEvent(); }