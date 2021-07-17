/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019 [WSL: Ubuntu]
** File description:
** IGameModule
*/

#pragma once

#include <string>

class IGameModule
{
public:
    virtual ~IGameModule() = default;

    virtual const std::string &getTextureFilepath() const = 0;

    virtual void update() = 0;
};