/*
** EPITECH PROJECT, 2020
** cpp_rush2_2019 [WSL: Ubuntu]
** File description:
** PapaXmasTable
*/

#include "PapaXmasTable.hpp"

PapaXmasTable::PapaXmasTable()
{
    _toyList[0] = nullptr;
    _boxList[0] = nullptr;
    _paperList[0] = nullptr;
}

PapaXmasTable::~PapaXmasTable()
{
    while (_toyList[0] != nullptr)
        delete takeToy();
    while (_boxList[0] != nullptr)
        delete takeBox();
    while (_paperList[0] != nullptr)
        delete takePaper();
}

static int getSize(Object * const *list)
{
    int i = 0;

    for (; list[i] != nullptr; i++);
    return i;
}

std::string *PapaXmasTable::getTitle() const
{
    int i = 0;
    std::string *titles = new std::string[getSize(_toyList)+getSize(_boxList)+getSize(_paperList)+1];

    for (int j = 0; _toyList[j] != nullptr; j++, i++)
        titles[i] = _toyList[j]->getTitle();
    for (int j = 0; _boxList[j] != nullptr; j++, i++)
        titles[i] = _boxList[j]->getTitle();
    for (int j = 0; _paperList[j] != nullptr; j++, i++)
        titles[i] = _paperList[j]->getTitle();
    titles[i] = "";
    return titles;
}

void PapaXmasTable::addToy(Object *&obj)
{
    int size = getSize(_toyList);

    if (obj == nullptr)
        return;
    _toyList[size] = obj;
    _toyList[size+1] = nullptr;
    obj = nullptr;
    if (getSize(_toyList) + getSize(_boxList) + getSize(_paperList) > 10) {
        std::cerr << "There is too much objects on the table!!!" << std::endl;
        exit(84);
    }
}

void PapaXmasTable::addBox(Object *&obj)
{
    int size = getSize(_boxList);

    if (obj == nullptr)
        return;
    _boxList[size] = obj;
    _boxList[size+1] = nullptr;
    obj = nullptr;
    if (getSize(_toyList) + getSize(_boxList) + getSize(_paperList) > 10) {
        std::cerr << "There is too much objects on the table!!!" << std::endl;
        exit(84);
    }
}

void PapaXmasTable::addPaper(Object *&obj)
{
    int size = getSize(_paperList);

    if (obj == nullptr)
        return;
    _paperList[size] = obj;
    _paperList[size+1] = nullptr;
    obj = nullptr;
    if (getSize(_toyList) + getSize(_boxList) + getSize(_paperList) > 10) {
        std::cerr << "There is too much objects on the table!!!" << std::endl;
        exit(84);
    }
}

Object *PapaXmasTable::takeToy()
{
    Object *obj = _toyList[0];

    if (obj == nullptr)
        return obj;
    for (int i = 1; i < getSize(_toyList); i++)
        _toyList[i-1] = _toyList[i];
    _toyList[getSize(_toyList)-1] = nullptr;
    return obj;
}

Object *PapaXmasTable::takeBox()
{
    Object *obj = _boxList[0];

    if (obj == nullptr)
        return obj;
    for (int i = 1; i < getSize(_boxList); i++)
        _boxList[i-1] = _boxList[i];
    _boxList[getSize(_boxList)-1] = nullptr;
    return obj;
}

Object *PapaXmasTable::takePaper()
{
    Object *obj = _paperList[0];

    if (obj == nullptr)
        return obj;
    for (int i = 1; i < getSize(_paperList); i++)
        _paperList[i-1] = _paperList[i];
    _paperList[getSize(_paperList)-1] = nullptr;
    return obj;
}

Box *PapaXmasTable::getFirstBox()
{
    if (_boxList[0] == nullptr)
        return nullptr;
    return dynamic_cast<Box *>(_boxList[0]);
}

GiftPaper *PapaXmasTable::getFirstPaper()
{
    if (_paperList[0] == nullptr)
        return nullptr;
    return dynamic_cast<GiftPaper *>(_paperList[0]);
}

bool PapaXmasTable::toyIsEmpty()
{
    return _toyList[0] == nullptr;
}

bool PapaXmasTable::boxIsEmpty()
{
    return _boxList[0] == nullptr;
}

bool PapaXmasTable::paperIsEmpty()
{
    return _paperList[0] == nullptr;
}
