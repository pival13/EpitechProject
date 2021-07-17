/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019 [WSL: Ubuntu]
** File description:
** IDisplayModule
*/

#include <string>

class IDisplayModule
{
public:
    virtual ~IDisplayModule() = default;

    virtual void updateEvent() = 0;
    virtual void setTexture(const std::string & fileName) = 0;
    virtual void display() = 0;
};