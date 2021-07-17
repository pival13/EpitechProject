/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019 [WSL: Ubuntu]
** File description:
** AGameModule
*/

#include "AGameModule.hpp"

AGameModule::AGameModule(ArcadeContent &ac, const std::string &texturePath)
: Module(ac), _texturePath("games/" + texturePath)
{
}

const std::string &AGameModule::getTextureFilepath() const { return _texturePath; }

char AGameModule::getMapAt(int x, int y) const noexcept(false) { return Module::getMapAt(x, y); }
char AGameModule::getMapAt(const std::array<int, 2> &pos) const noexcept(false) { return Module::getMapAt(pos[0], pos[1]); }
char AGameModule::getMapAt(const std::array<size_t, 2> &pos) const noexcept(false) { return Module::getMapAt((int)pos[0], (int)pos[1]); }
size_t AGameModule::getMapWidth() const { return Module::getMapWidth(); }
size_t AGameModule::getMapHeight() const { return Module::getMapHeight(); }

bool AGameModule::isKeyUp() const { return Module::isKeyUp(); }
bool AGameModule::isKeyRight() const { return Module::isKeyRight(); }
bool AGameModule::isKeyDown() const { return Module::isKeyDown(); }
bool AGameModule::isKeyLeft() const { return Module::isKeyLeft(); }
bool AGameModule::isKeyEnter() const { return Module::isKeyEnter(); }
bool AGameModule::isKeyBack() const { return Module::isKeyBack(); }
bool AGameModule::isKeyPressed() const { return Module::isKeyPressed(); }
bool AGameModule::isKeyReleased() const { return Module::isKeyReleased(); }

void AGameModule::setMapAt(int x, int y, char c) noexcept(false) { return Module::setMapAt(x, y, c); }
void AGameModule::setMapAt(const std::array<int, 2> &pos, char c) noexcept(false) { return Module::setMapAt(pos[0], pos[1], c); }
void AGameModule::setMapAt(const std::array<size_t, 2> &pos, char c) noexcept(false) { return Module::setMapAt((int)pos[0], (int)pos[1], c); }
void AGameModule::cleanMap() { return Module::cleanMap(); }

void AGameModule::backToMenu() { return Module::backToMenu(true); }