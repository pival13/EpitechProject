/*
** EPITECH PROJECT, 2020
** ConveyorBelt.hpp
** File description:
** ConveyorBelt.hpp
*/

#include "ConveyorBelt.hpp"

PapaXmasConveyorBelt::PapaXmasConveyorBelt() : _typewrap(true)
{
    _conv_obj = nullptr;
}

PapaXmasConveyorBelt::~PapaXmasConveyorBelt()
{
}

void PapaXmasConveyorBelt::InButton()
{
    if (_conv_obj != nullptr)
        return;
    if (_typewrap) {
        _conv_obj = new Box();
    }
    else {
        _conv_obj = new GiftPaper();
    }
    _typewrap = !_typewrap;
}

void PapaXmasConveyorBelt::OutButton()
{
    if (_conv_obj == nullptr)
        return;
    if (_conv_obj->getTitle() == "Box" || _conv_obj->getTitle() == "GiftPaper") {
        delete _conv_obj;
        _conv_obj = nullptr;
    }
    else
        std::cerr << "The object is neither a wrap or a gift!" \
                  <<" Can't destroy it or deliver it to Santa" << std::endl;
}

bool PapaXmasConveyorBelt::isEmpty() const
{
    if (_conv_obj)
        return (false);
    return (true);
}

Object *&PapaXmasConveyorBelt::getObject()
{
    static Object *tmp = nullptr;
    tmp = _conv_obj;
    _conv_obj = nullptr;
    return tmp;
}
    
void PapaXmasConveyorBelt::addObject(Object *&obj)
{
    _conv_obj = obj;
    obj = nullptr;
}
