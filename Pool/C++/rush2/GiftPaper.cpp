/*
** EPITECH PROJECT, 2020
** rush2 [WSL: Ubuntu]
** File description:
** GiftPaper
*/

#include "GiftPaper.hpp"

GiftPaper::GiftPaper()
: Object("GiftPaper")
{
    _Type = GIFTPAPER;
    _object = nullptr;
}

GiftPaper::~GiftPaper()
{
    if (_object != nullptr) {
        int type = _object->getType();
        if (type == 0) {
            Box *box = dynamic_cast<Box *>(_object);
            delete(box);
        } else if (type == 1) {
            GiftPaper *paper = dynamic_cast<GiftPaper *>(_object);
            delete(paper);
        } else {
            if (type == 2) {
                LittlePony *pony = dynamic_cast<LittlePony *>(_object);
                delete(pony);
            } else {
                Teddy *teddy = dynamic_cast<Teddy *>(_object);
                delete(teddy);
            }
        }
    }
}

bool GiftPaper::wrapMeThat(Object *&pObject)
{
    if (!pObject) {
        std::cerr << "Can't wrap something if the Paper isn't open (You have to open it before)" << std::endl;
        return (false);
    } else if (_object != nullptr) {
        std::cerr << "There is already something in the Box (You have to empty the box before)" << std::endl;
        return (false);
    }
    _object = pObject;
    pObject = nullptr;
    return (true);
}
