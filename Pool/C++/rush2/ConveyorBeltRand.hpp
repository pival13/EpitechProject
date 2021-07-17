/*
** EPITECH PROJECT, 2020
** ConveyorBeltRand.hpp
** File description:
** ConveyorBeltRand.hpp
*/

#pragma once

#include "ConveyorBelt.hpp"
#include <fstream>

class ConveyorBeltRand : public IConveyorBelt{
public:
    ConveyorBeltRand();
    ~ConveyorBeltRand();

    void InButton();
    void object_to_xml();
    void OutButton();
    bool isEmpty() const;
    Object *&getObject();
    void addObject(Object *&obj);

private:
    bool _typewrap;
    std::ofstream out;
};
