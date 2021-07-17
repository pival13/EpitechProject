/*
** EPITECH PROJECT, 2020
** ConveyorBelt.cpp
** File description:
** ConveyorBelt.cpp
*/

#pragma once

#include "IConveyorBelt.hpp"
#include "Box.hpp"
#include "GiftPaper.hpp"
#include <string>

class PapaXmasConveyorBelt : public IConveyorBelt
{
public:
    PapaXmasConveyorBelt();
    ~PapaXmasConveyorBelt();

    void InButton();
    void OutButton();
    bool isEmpty() const;
    Object *&getObject();
    void addObject(Object *&obj);

private:
    bool _typewrap;
};
