/*
** By Kevin Pruvost, May 2020
** File description:
** ZappyRenderWindow class.
*/

#include "ZappyRenderWindow.hpp"

// C++ includes
#include <functional>

ZappyRenderWindow::ZappyRenderWindow(const sf::VideoMode & videoMode, const std::string & name,
sf::Uint32 style)
    : sf::RenderWindow(videoMode, name, style)
{
}

ZappyRenderWindow::~ZappyRenderWindow()
{

}

void ZappyRenderWindow::draw(TextObject & obj)
{
    sf::RenderWindow::draw(obj);
}

void ZappyRenderWindow::draw(InterfaceTextObject & obj)
{
    obj.setPosition(sf::Vector2f(
        getView().getCenter().x - getView().getSize().x / 2 + (obj.pos.x * actualZoom),
        getView().getCenter().y - getView().getSize().y / 2 + (obj.pos.y * actualZoom)));
    obj.setScale(actualZoom, actualZoom);
    (this->*(static_cast<void (ZappyRenderWindow::*)(TextObject &)>(&ZappyRenderWindow::draw)))(obj);
}

void ZappyRenderWindow::draw(Object & obj)
{
    obj.performAnimation();
    obj.performProgressiveMove();
    sf::RenderWindow::draw(obj);
    for (auto & textObj : obj._textObjects)
    {
        textObj.setPosition(obj.getPosition().x + textObj.pos.x, obj.getPosition().y + textObj.pos.y);
        draw(textObj);
    }
}

void ZappyRenderWindow::draw(InterfaceObject & obj)
{
    obj.setPosition(sf::Vector2f(
        getView().getCenter().x - getView().getSize().x / 2 + (obj.pos.x * actualZoom),
        getView().getCenter().y - getView().getSize().y / 2 + (obj.pos.y * actualZoom)));
    obj.setScale(actualZoom, actualZoom);
    obj.performAnimation();
    obj.performProgressiveMove();
    sf::RenderWindow::draw(obj);
    for (auto & textObj : obj._textObjects)
    {
        textObj.setScale(actualZoom, actualZoom);
        textObj.setPosition(obj.getPosition().x + (textObj.pos.x * actualZoom), obj.getPosition().y + (textObj.pos.y * actualZoom));
        draw(textObj);
    }
}

void ZappyRenderWindow::draw(Floor & tile)
{
    (this->*(static_cast<void (ZappyRenderWindow::*)(Object &)>(&ZappyRenderWindow::draw)))(tile);
    for (int i = 0; i <= InventoryData::InventoryDataEnum::THYSTMANE; ++i)
    {
        if (tile.inventory[i] > 0)
            draw(tile.inventorySprites[i]);
    }
}

void ZappyRenderWindow::draw(Mob & mob)
{
    (this->*(static_cast<void (ZappyRenderWindow::*)(Object &)>(&ZappyRenderWindow::draw)))(mob);
}

void ZappyRenderWindow::draw(Cursor & cursor)
{
    auto highlight = cursor.getHighlight();
    if (highlight)
        sf::RenderWindow::draw(*highlight->get());
    static auto func = static_cast<void (ZappyRenderWindow::*)(InterfaceObject &)>(&ZappyRenderWindow::draw);
    (this->*func)(cursor);
}

void ZappyRenderWindow::zoom(float zoomMultiplier)
{
    actualZoom *= zoomMultiplier;
    auto view = getView();
    view.zoom(zoomMultiplier);
    setView(view);
}

void ZappyRenderWindow::draw(BottomButton & obj)
{
    obj.setPosition(sf::Vector2f(
        getView().getCenter().x - getView().getSize().x / 2 + (obj.pos.x * actualZoom),
        getView().getCenter().y - getView().getSize().y / 2 + (obj.pos.y * actualZoom)));
    obj.setScale(actualZoom, actualZoom);
    obj.performAnimation();
    obj.performProgressiveMove();
    sf::RenderWindow::draw(obj);
    for (auto & textObj : obj._textObjects)
    {
        textObj.setScale(actualZoom, actualZoom);
        textObj.setPosition(
            obj.getPosition().x - obj.getGlobalBounds().width / 2 + (textObj.pos.x * actualZoom),
            obj.getPosition().y - obj.getGlobalBounds().height / 2 + (textObj.pos.y * actualZoom));
        draw(textObj);
    }
    for (auto & textObj : obj._objects)
    {
        textObj.setScale(actualZoom, actualZoom);
        textObj.setPosition(obj.getPosition().x + (textObj.pos.x * actualZoom), obj.getPosition().y + (textObj.pos.y * actualZoom));
        draw(textObj);
    }
}

void ZappyRenderWindow::draw(KVector<BottomButton> & obj)
{
    int x = 540;
    int y = getSize().y - 85;

    for (auto & button : obj)
    {
        button.setInterfacePosition(x, y);
        x += button.getTextureRect().width + 10;
        draw(button);
    }
}

float ZappyRenderWindow::getActualZoom() { return actualZoom; }