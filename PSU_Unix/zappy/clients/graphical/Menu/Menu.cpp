/*
** By Kevin Pruvost, May 2020
** File description:
** Menu class.
*/

#include "Menu.hpp"

Menu::Menu(ZappyRenderWindow & window)
    : _title(Constants::TextureId::MENU_TITLE, 0, 0)
    , _planet(Constants::TextureId::MENU_PLANET, 0, 0)
    , _background(Constants::TextureId::MENU_BACKGROUND, 0, 0)
    , _play(Constants::TextureId::MENU_PLAY, 0, 0)
    , _quit(Constants::TextureId::MENU_QUIT, 0, 0)
    , _cursor(Constants::TextureId::CURSOR)
{
    _background.setOrigin(_background.getTextureRect().width / 2, 0);
    _planet.centerObject();

    _planet.setInterfacePosition(window.getSize().x / 2, window.getSize().y);

    _title.setInterfacePosition(
        window.getSize().x / 2 - _title.getTextureRect().width / 2, 100);

    _play.setInterfacePosition(
        window.getSize().x / 2 - _play.getTextureRect().width / 2, 400);

    _quit.setInterfacePosition(
        window.getSize().x / 2 - _quit.getTextureRect().width / 2, 450 + _play.getTextureRect().height);
}

Menu::~Menu()
{
}

int Menu::compute(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client)
{
    _cursor.updatePosition(window);
    checkCursorHighlight();

    (event.type == sf::Event::MouseButtonPressed) ? _cursor.clickAnimation() : _cursor.noClickAnimation();

    if (_cursor.pointedObject != nullptr)
    {
        if (event.type == sf::Event::MouseButtonReleased)
        {
            if (event.mouseButton.button == sf::Mouse::Button::Left)
            {
                if (_cursor.pointedObject == &_play)
                    return PageId::GAME_PAGE;
                else if (_cursor.pointedObject == &_quit)
                    window.close();
            }
            else if (event.mouseButton.button == sf::Mouse::Button::Right)
            {

            }
        }
    }
    return EXIT_SUCCESS;
}

int Menu::draw(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client)
{
    animateBackground(20);

    if (window.getActualZoom() != 1)
        window.zoom(1.f / window.getActualZoom());

    for (auto & obj : _objects)
        window.draw(obj);
    window.draw(_background);
    window.draw(_title);
    window.draw(_planet);
    window.draw(_play);
    window.draw(_quit);
    window.draw(_cursor);
    return EXIT_SUCCESS;
}

void Menu::animateBackground(float speed)
{
    static auto start = std::chrono::steady_clock::now();
    static float angle = 0;
    auto end = std::chrono::steady_clock::now();
    auto elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    if (elapsedMs >= speed)
    {
        start = std::chrono::steady_clock::now();
        _background.pos.x += _background.texture->getSize().x / 1000;
        if (_background.pos.x >= (int)_background.texture->getSize().x / 2)
            _background.pos.x -= _background.texture->getSize().x / 2;
        angle += 0.1;
        if (angle >= 360)
            angle = 0;
    }
    _background.setPosition(_background.pos.x, _background.pos.y);
    _planet.setRotation(angle);
}

void Menu::checkCursorHighlight()
{
    if (_cursor.highlightObject(_play))
        return;

    if (_cursor.highlightObject(_quit))
        return;

    _cursor.resetHighlight();
}