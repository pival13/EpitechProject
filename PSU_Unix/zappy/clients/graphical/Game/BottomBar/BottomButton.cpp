/*
** By Kevin Pruvost, June 2020
** File description:
** BottomButton class.
*/

#include "BottomButton.hpp"

BottomButton::BottomButton(Constants::TextureId textureId, int x, int y)
    : InterfaceObject(textureId)
{
    setInterfacePosition(x, y);
}

void BottomButton::setString(const std::string & str)
{
    if (!_textObjects.empty())
    {
        _textObjects[0].setString(str);
    }
}

std::string BottomButton::getString()
{
    if (!_textObjects.empty())
        return _textObjects[0].getString();
    return "";
}

void BottomButton::setIconTexture(Constants::TextureId textureId)
{
    if (!_objects.empty())
        _objects[0].changeTexture(textureId);
}

BottomButton::~BottomButton()
{
}