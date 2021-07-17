/*
** EPITECH PROJECT, 2020
** cpp_rush2_2019 [WSL: Ubuntu]
** File description:
** ITable
*/

#pragma once

#include "Teddy.hpp"
#include "LittlePony.hpp"
#include "Box.hpp"
#include "GiftPaper.hpp"
#include <list>

class ITable {
    public:
        virtual ~ITable() {}

        virtual std::string *getTitle() const = 0;
        virtual void addToy(Object *&) = 0;
        virtual void addBox(Object *&) = 0;
        virtual void addPaper(Object *&) = 0;
        virtual Object *takeToy() = 0;
        virtual Object *takeBox() = 0;
        virtual Object *takePaper() = 0;
        virtual bool toyIsEmpty() = 0;
        virtual bool boxIsEmpty() = 0;
        virtual bool paperIsEmpty() = 0;
        virtual Box *getFirstBox() = 0;
        virtual GiftPaper *getFirstPaper() = 0;

    protected:
        Object * _toyList[11];
        Object * _boxList[11];
        Object * _paperList[11];

    private:
};
