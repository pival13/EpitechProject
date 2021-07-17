/*
** EPITECH PROJECT, 2020
** ConveyorBeltRand.cpp
** File description:
** ConveyorBeltRand.cpp
*/

#include "ConveyorBeltRand.hpp"

ConveyorBeltRand::ConveyorBeltRand() : _typewrap(true), out("output.xml")
{
    int nb = random()%4;


    if (nb == 1) {
        _conv_obj = nullptr;
    }
    else if (nb == 2) {
        _conv_obj = new Box();
    }
    else
        _conv_obj = new GiftPaper();
}

ConveyorBeltRand::~ConveyorBeltRand()
{
    out.close();
}

void ConveyorBeltRand::InButton()
{
    if (_conv_obj != nullptr) {
        std::cerr << "The conveyor is full. Please empty it." << std::endl;
        return;
    }
    if (random() % 2 == 0) {
        _conv_obj = new Box();
    }
    else {
        _conv_obj = new GiftPaper();
    }
    _typewrap = !_typewrap;
}

void ConveyorBeltRand::object_to_xml()
{
    if (_conv_obj->getType() == 1) {
        GiftPaper *tmp_paper = dynamic_cast<GiftPaper*> (_conv_obj);
        out << "<GiftPaper>";
        if (tmp_paper->getObject() != nullptr && tmp_paper->getObject()->getType() == 0) {
            out << "<Box>";
            Box *tmp_box = dynamic_cast<Box*> (tmp_paper->getObject());
            if (tmp_box->getObject() != nullptr && tmp_box->getObject()->getType() == 3)
                out << "<Teddy>" << tmp_box->getObject()->getTitle() << "</Teddy>";
            else if (tmp_box->getObject()->getType() == 2) {
                out << "<Littlepony>" << tmp_box->getObject()->getTitle() << "</Littlepony>";
            }
            out << "</Box>";
        }
        else if (tmp_paper->getObject() != nullptr && tmp_paper->getObject()->getType() == 3)
            out << "<Teddy>" << tmp_paper->getObject()->getTitle() << "</Teddy>";
        else if (tmp_paper->getObject()->getType() == 2)
            out << "<Littlepony>" << tmp_paper->getObject()->getTitle() << "</Littlepony>";
        out << "</GiftPaper>" << std::endl;
    }
    if (_conv_obj->getType() == 0) {
        out << "<Box>";
        Box *tmp_box = dynamic_cast<Box*> (_conv_obj);
        if (tmp_box->getObject() != nullptr && tmp_box->getObject()->getType() == 3)
            out << "<Teddy>" << tmp_box->getObject()->getTitle() << "</Teddy>";
        else if (tmp_box->getObject()->getType() == 2)
            out << "<Littlepony>" << tmp_box->getObject()->getTitle() << "</Littlepony>";
        out << "</Box>" << std::endl;;
    }
}

void ConveyorBeltRand::OutButton()
{
    if (_conv_obj == nullptr) {
        std::cerr << "The conveyer is empty. Please put something." << std::endl;
        return;
    }
    if (_conv_obj->getTitle() == "Box" || _conv_obj->getTitle() == "GiftPaper") {
        object_to_xml();
        delete _conv_obj;
        _conv_obj = nullptr;
    }
    else
        std::cerr << "The object is neither a wrap or a gift!" \
                  << " Can't destroy it or deliver it to Santa" << std::endl;
}

bool ConveyorBeltRand::isEmpty() const
{
    if (_conv_obj)
        return (false);
    return (true);
}

Object *&ConveyorBeltRand::getObject()
{
    static Object *tmp = nullptr;
    tmp = _conv_obj;
    _conv_obj = nullptr;
    return tmp;
}
    
void ConveyorBeltRand::addObject(Object *&obj)
{
    _conv_obj = obj;
    obj = nullptr;
}
