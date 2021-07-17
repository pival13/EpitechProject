/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** Windows
*/

#include "Windows.hpp"

Windows::Windows(const std::string &title, GameObject *parent)
: GameObject(parent), _window(sf::VideoMode(1280, 720), title), _isOpen(true)
{
    _window.clear(sf::Color::White);
    _window.setFramerateLimit(60);
}

Windows::~Windows()
{
}

void Windows::setIcon(const std::string &file)
{
    sf::Image img;
    if (img.loadFromFile(file))
        _window.setIcon(img.getSize().x, img.getSize().y, img.getPixelsPtr());
}

void Windows::draw(Drawable &d)
{
    _window.draw(d.getSprite());
}

void Windows::display()
{
    _window.display();
    _window.clear(sf::Color::White);
}

Event Windows::getEvents()
{
    Event ret;
    sf::Event ev;

    while (_window.pollEvent(ev)) {
        if (ev.type == sf::Event::Closed)
            _isOpen = false;
        else if (ev.type == sf::Event::KeyPressed) {
            auto &p = ret.events.emplace_back();
            p.first = Event::EventType::KeyPressed;
            p.second.key = ev.key.code;
        } else if (ev.type == sf::Event::KeyReleased) {
            auto &p = ret.events.emplace_back();
            p.first = Event::EventType::KeyReleased;
            p.second.key = ev.key.code;
        } else if (ev.type == sf::Event::MouseButtonPressed) {
            if (ev.mouseButton.button <= sf::Mouse::Middle) {
                auto &p = ret.events.emplace_back();
                p.first = Event::EventType::MousePressed;
                p.second.mouseButton = (ev.mouseButton.button == sf::Mouse::Left ? Event::EventTouch::LeftClick : 
                    (ev.mouseButton.button == sf::Mouse::Right ? Event::EventTouch::RightClick : Event::EventTouch::Wheel));
            }
        } else if (ev.type == sf::Event::MouseButtonReleased) {
            if (ev.mouseButton.button <= sf::Mouse::Middle) {
                auto &p = ret.events.emplace_back();
                p.first = Event::EventType::MouseReleased;
                p.second.mouseButton = (ev.mouseButton.button == sf::Mouse::Left ? Event::EventTouch::LeftClick : 
                    (ev.mouseButton.button == sf::Mouse::Right ? Event::EventTouch::RightClick : Event::EventTouch::Wheel));
            }
        }
    }
    ret.mousePosition = {double(sf::Mouse::getPosition(_window).x), double(sf::Mouse::getPosition(_window).y)};
    ret.mouseRightIsPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);
    ret.mouseLeftIsPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
    ret.mouseWheelIsPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle);
    ret.ctrlIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl);
    ret.altIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RAlt) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LAlt);
    ret.shiftIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift);
    return ret;
}