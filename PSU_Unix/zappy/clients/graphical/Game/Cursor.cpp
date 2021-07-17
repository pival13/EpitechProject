/*
** By Kevin Pruvost, May 2020
** File description:
** Cursor class.
*/

#include "Cursor.hpp"

Cursor::Cursor(Constants::TextureId tID)
    : InterfaceObject(tID, 0, 0)
{
    setOrigin(0, 0);
}

Cursor::~Cursor()
{

}

void Cursor::updatePosition(IZappyRenderWindow & window)
{
    pos = sf::Mouse::getPosition(window);
    setPosition(sf::Vector2f(
        window.getView().getCenter().x - window.getView().getSize().x / 2 + (pos.x * window.getActualZoom()),
        window.getView().getCenter().y - window.getView().getSize().y / 2 + (pos.y * window.getActualZoom())));
}

bool Cursor::highlightObject(Object & object)
{
    if (!object.isVisible())
        return false;
    auto pos = getPosition();
    auto gbounds = object.getGlobalBounds();
    if (pos.x >= gbounds.left && pos.x <= gbounds.left + gbounds.width)
    {
        if (pos.y >= gbounds.top && pos.y <= gbounds.top + gbounds.height)
        {
            if (pointedObject == &object)
                return refreshHighlight();
            if (!_highlightReleased)
                resetHighlight();
            pointedObject = &object;
            _highlight.reset(new Object(object.textureId));
            _highlightReleased = false;
            _highlight->setColor(sf::Color(100, 100, 100, 150));
            return refreshHighlight();
        }
    }
    return false;
}

bool Cursor::refreshHighlight()
{
    _highlight->setPosition(pointedObject->getPosition());
    _highlight->setTexture(*pointedObject->getTexture());
    _highlight->setTextureRect(pointedObject->getTextureRect());
    _highlight->setOrigin(pointedObject->getOrigin());
    _highlight->setScale(pointedObject->getScale());
    return true;
}

void Cursor::resetHighlight()
{
    _highlight.release();
    _highlightReleased = true;
    pointedObject = nullptr;
}

std::unique_ptr<Object> * Cursor::getHighlight()
{
    if (!_highlightReleased)
        return &_highlight;
    return nullptr;
}

void Cursor::clickAnimation()
{
    if (_clickAnimationState)
        return;
    _clickAnimationState = true;

    animate(AnimateOptions::EndsOnLastFrame, 0.07, 0);
}

void Cursor::noClickAnimation()
{
    if (!_clickAnimationState)
        return;
    _clickAnimationState = false;

    animate(AnimateOptions::EndsOnLastFrame, 0.07, 1);
}