/*
** EPITECH PROJECT, 2020
** cpp_rush3_2019
** File description:
** Graphic
*/

#include "./Graphic.hpp"

Graphic::Graphic()
: _vm(_dimWin.x, _dimWin.y), _window(_vm, "MyGKrellm", sf::Style::Titlebar), _textureMod(), _textureModIn(), _textureModDate()
{
    _textureMod.loadFromFile("./Sfml/Assets/textureMod.png");
    _textureModIn.loadFromFile("./Sfml/Assets/textureModIn.png");
    _textureModDate.loadFromFile("./Sfml/Assets/textureModDate.png");
    _font.loadFromFile("./Sfml/Assets/Timeless.ttf");

    _modules.push_back(new ModuleGraph(new ModuleDatetime()));
    _modules.push_back(new ModuleGraph(new ModuleName()));
    _modules.push_back(new ModuleGraph(new ModuleOSCore()));
    _modules.push_back(new ModuleGraph(new ModuleMemory()));
    //_modules.push_back(new ModuleGraph(new ModuleCPU()));

    for (ModuleGraph *a : _modules) {
        if (a->getModule().isDrawable()) {
            if (a->getModule().getName() == "Memory") {
                a->getSpriteMod().setTexture(_textureModDate);
                a->getSpriteModIn().setTexture(_textureModDate);
            }else {
                a->getSpriteMod().setTexture(_textureMod);
                a->getSpriteModIn().setTexture(_textureModIn);
            }
        } else {
            a->getSpriteMod().setTexture(_textureModDate);
            a->getSpriteModIn().setTexture(_textureModDate);
        }
    }
    setStatus();
    calcY();
    fillText();
}

Graphic::~Graphic()
{
}

sf::Text Graphic::stringToText(std::string &name)
{
    sf::Text newText(name, _font, 13);
    newText.setFillColor(sf::Color(250, 250, 245, 255));
    newText.setScale(sf::Vector2f(0.9f, 0.9f));
    return newText;
}

sf::RectangleShape *Graphic::stringToRect(std::string &str, int tot)
{
    float nbr = atof(str.c_str());
    sf::RectangleShape *rect = new sf::RectangleShape;

    int xCreated = (nbr * 180) / tot;
    rect->setSize(sf::Vector2f(xCreated, 17.0f));
    return rect;
}


void Graphic::fillText()
{
    int tabCPU[60] = {0};
    int index = 0;
    for (ModuleGraph *a : _modules) {
        if (a->getModule().getName() == "Name") a->setTextTwo(stringToText(a->getModule().getOneInfo()["Hostname"]), (stringToText(a->getModule().getOneInfo()["Username"])));
        else if (a->getModule().getName() == "Date & Time") a->setTextTwo(stringToText(a->getModule().getOneInfo()["Time"]), (stringToText(a->getModule().getOneInfo()["Date"])));
        else if (a->getModule().getName() == "Informations system") a->setTextTwo(stringToText(a->getModule().getOneInfo()["Kernel"]), (stringToText(a->getModule().getOneInfo()["OSName"])));
        else if (a->getModule().getName() == "Memory") {
            std::string memory("Memory");
            std::string swap("Swap");
            a->resetMemorySwapArray();
            a->setTextTwo(stringToText(memory), stringToText(swap));
            int _memTot = atoi(a->getModule().getSixtyInfo()["MemTotal"].front().c_str());
            int _swapTot = atoi(a->getModule().getSixtyInfo()["SwapTotal"].front().c_str());
            a->setMemorySwapArray(stringToRect(a->getModule().getSixtyInfo()["MemTotal"].front(), _memTot), sf::Color::Red);
            a->setMemorySwapArray(stringToRect(a->getModule().getSixtyInfo()["MemFree"].front(),_memTot), sf::Color::Green);
            a->setMemorySwapArray(stringToRect(a->getModule().getSixtyInfo()["Cached"].front(), _memTot), sf::Color::Yellow);
            a->setMemorySwapArray(stringToRect(a->getModule().getSixtyInfo()["Buffers"].front(), _memTot), sf::Color::Yellow);
            a->setMemorySwapArray(stringToRect(a->getModule().getSixtyInfo()["SwapTotal"].front(), _swapTot), sf::Color::Red);
            a->setMemorySwapArray(stringToRect(a->getModule().getSixtyInfo()["SwapFree"].front(), _swapTot), sf::Color::Green);
        }else if (a->getModule().getName() == "CPU") {
            a->resetSticks();
            int nbrCPU = a->getModule().getSixtyInfo().size() - 3;
            float maxHz = atof(a->getModule().getSixtyInfo()["MaxFreq"].front().c_str()) / 9;

            for (int i = 0; i < nbrCPU; i++) {
                std::string nameCpu = "CPU ";
                std::list<std::string> info = a->getModule().getSixtyInfo()[nameCpu + char((i + '0'))];
                for (std::string b : info) {
                    tabCPU[i] += atoi(b.c_str());
                    index++;
                }
                index = 0;
            }

            a->createStick(tabCPU, maxHz);
            
        }
    }
}

void Graphic::calcY()
{
    _dimWin.y = 0;
    for (const ModuleGraph *a : _modules) {
        if (a->getModule().isDrawable()) {
            if (a->getModule().getName() == "Memory") {
                _dimWin.y += (17 * 4);
                _nbrMod += 3;
            }else {
                _nbrModGraph++;
                _dimWin.y += 52; // 52 = Taille Y (textureModIn + textureMod)
            }
        }else {
            if (a->getModule().getName() == "Name" || a->getModule().getName() == "Date & Time" || a->getModule().getName() == "Informations system") {
                _nbrMod++;
                _dimWin.y += 17;
            }
            _dimWin.y += 17;
        }
        _nbrMod++;
    }
    _dimWin.x = 180;
    _window.setSize(sf::Vector2u(_dimWin));
}

void Graphic::setStatus()
{
    for (ModuleGraph *a : _modules)
        _status.insert(std::pair<std::string, bool>(a->getModule().getName(), a->getModule().getStatus()));
}

void Graphic::getEvents()
{
    while (_window.pollEvent(_evt)) {
        if (_evt.key.code == sf::Keyboard::Escape)
            _window.close();
        if (_evt.type == sf::Event::KeyReleased) {
            if (_evt.key.code == sf::Keyboard::M) {
                GraphicMenu menu(_status, _posWin);
                menu.menu();
            }
        }
        if (_evt.type == sf::Event::Resized) {
            sf::FloatRect visibleArea(0, 0, _evt.size.width, _evt.size.height);
            _window.setView(sf::View(visibleArea));
        }
    }
}

void Graphic::setPosMod()
{
    for (std::vector<ModuleGraph *>::iterator ite = _modules.begin(); ite != _modules.end(); ite++)
        if (ite == _modules.begin() ) {
            (*ite)->setPos(sf::Vector2f(0, 0));
        } else
            if ((*std::prev(ite, 1))->getModule().isDrawable()) {
                if ((*std::prev(ite, 1))->getModule().getName() == "Memory") {
                    (*ite)->setPos(sf::Vector2f(0, (*std::prev(ite, 1))->getPos().y + 17));
                }else {
                    (*ite)->setPos(sf::Vector2f(0, (*std::prev(ite, 1))->getPos().y + 52));
                }
            }else {
                (*ite)->setPos(sf::Vector2f(0, (*std::prev(ite, 1))->getPos().y + 17));
            }
}

void Graphic::drawModules()
{
    calcY();
    _window.clear(_colorWin);
    for (const ModuleGraph *a : _modules) {
        if (a->getModule().isDrawable()) {
            if (a->getModule().getName() == "Memory") {
                _window.draw(a->getSpriteModConst());
                _window.draw(a->getSpriteModInConst());
                _window.draw(a->getTextFirst());
                _window.draw(a->getTextSecond());
                for (const sf::RectangleShape *rect : a->getMemSwapArray()) {
                    _window.draw(*rect);
                }
            }else {
                _window.draw(a->getSpriteModConst());
                _window.draw(a->getTextFirst());
                _window.draw(a->getSpriteModInConst());
                for (Stick *a : a->getSticks()) {
                    _window.draw(a->_stick);
                }
            }
        }else {
            _window.draw(a->getSpriteModConst());
            _window.draw(a->getTextFirst());
            if (a->getModule().getName() == "Name" || a->getModule().getName() == "Informations system" || a->getModule().getName() == "Date & Time") {
                _window.draw(a->getSpriteModInConst());
                _window.draw(a->getTextSecond());
            }
        }
    }
    _window.display();
}

bool Graphic::isEnd() const
{
    return (!_window.isOpen());
}

void Graphic::updateModules()
{
    for (ModuleGraph *a : _modules)
        a->getModule().update();
    fillText();
    setPosMod();
}
