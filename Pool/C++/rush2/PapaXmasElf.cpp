/*
** EPITECH PROJECT, 2020
** cpp_rush2_2019 [WSL: Ubuntu]
** File description:
** PapaXmasElf
*/

#include "PapaXmasElf.hpp"

PapaXmasElf::PapaXmasElf()
{
    _hand = nullptr;
}

PapaXmasElf::~PapaXmasElf()
{
}

std::string *PapaXmasElf::look(const ITable &table) const
{
    return table.getTitle();
}

bool PapaXmasElf::createGift(ITable &table, IConveyorBelt &cBelt)
{
    Box *box;
    GiftPaper *paperGift;

    if (_hand != nullptr) //If hand not empty; return false
        putObject(table);
    if (table.toyIsEmpty()) { //If no toy on the table; return false
        std::cout << "o'pa ere's somin' wron' in da box!" << std::endl;
        return (false);
    }
    while (table.boxIsEmpty()) { //Check for avaible box
        if (cBelt.isEmpty())
            pushIN(cBelt);
        takeObject(cBelt);
        putObject(table);
    }
    takeToy(table); //Get the toy
    box = table.getFirstBox();
    box->openMe();
    if (box->wrapMeThat(_hand)) //Wrap toy in box
        std::cout << "tuuuut tuuut tuut" << std::endl;
    while (table.paperIsEmpty()) { //Check for avaible paper
        if (cBelt.isEmpty())
            pushIN(cBelt);
        takeObject(cBelt);
        putObject(table);
    }
    takeBox(table);
    paperGift = table.getFirstPaper();
    if (paperGift->wrapMeThat(_hand)) //Wrap box in paper
        std::cout << "tuuuut tuuut tuut" << std::endl;
    if (!cBelt.isEmpty()) {
        takeObject(cBelt);
        putObject(table);
    }
    takePaper(table); //Put paper in hand
    putObject(cBelt); //Put hand's object on convoyer
    pushOUT(cBelt); //Push out
    return (true);
}

void PapaXmasElf::putObject(ITable &table)
{
    if (_hand == nullptr)
        return;
    if (_hand->getTitle() == "Box")
        table.addBox(_hand);
    else if (_hand->getTitle() == "GiftPaper")
        table.addPaper(_hand);
    else
        table.addToy(_hand);
}

void PapaXmasElf::putObject(IConveyorBelt &cBelt)
{
    if (!cBelt.isEmpty()) {
        std::cerr << "The conveyer belt isn't empty. Press OUT button before adding a new gift on it" << std::endl;
        return;
    }
    cBelt.addObject(_hand);
}

void PapaXmasElf::takeToy(ITable &table)
{
    if (_hand != nullptr)
        putObject(table);
    _hand = table.takeToy();
    if (_hand != nullptr)
        dynamic_cast<Toy *>(_hand)->isTaken();
}

void PapaXmasElf::takeBox(ITable &table)
{
    if (_hand != nullptr)
        putObject(table);
    _hand = table.takeBox();
    if (_hand != nullptr)
        std::cout << "whistles while working" << std::endl;
}

void PapaXmasElf::takePaper(ITable &table)
{
    if (_hand != nullptr)
        putObject(table);
    _hand = table.takePaper();
    if (_hand != nullptr)
        std::cout << "whistles while working" << std::endl;
}

void PapaXmasElf::takeObject(IConveyorBelt &cBelt)
{
    if (_hand != nullptr)
        return;
    _hand = cBelt.getObject();
}

void PapaXmasElf::pushIN(IConveyorBelt &cBelt) const
{
    if (_hand != nullptr)
        return;
    cBelt.InButton();
}

void PapaXmasElf::pushOUT(IConveyorBelt &cBelt) const
{
    if (_hand != nullptr)
        return;
    cBelt.OutButton();
}
