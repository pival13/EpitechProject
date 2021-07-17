/*
** By Kevin Pruvost, May 2020
** File description:
** Game class.
*/

#include "Game.hpp"

static std::mutex mutex;

Game::Game(GraphicalClient & client, ZappyRenderWindow & window, sf::Event & event)
    : _background(Constants::TextureId::SKY_BACKGROUND)
    , _cursor(Constants::TextureId::CURSOR)
    , _objectDescriptionPanel(Constants::TextureId::DESC_PANEL, 0, 0)
    , _bottomBar(Constants::TextureId::GAME_OVERLAY, 0, 0)
    , _tvBackground(Constants::TextureId::TV_BACKGROUND, 100, 0)
    , _face(Constants::TextureId::FACE_FLOOR, 100, 0)
    , _tvEffect(Constants::TextureId::TV_EFFECT, 100, 0)
    , _compass(Constants::TextureId::COMPASS, 100, 0)
    , _compassCursor(Constants::TextureId::COMPASS_CURSOR, 100, 0)
    , _timePanel(Constants::TextureId::TIME_PANEL, 1800, 10)
    , _timeSetButton(Constants::TextureId::TIME_SET_BUTTON, 1800, 110)
    , _timeText(Constants::TextureId::TIME_TEXT_SPACE, 1800, 50)
    , _displayWin(Constants::FontId::STARCRAFT_FONT, "", 960, 540)
    , _playersButton(Constants::TextureId::BOTTOM_PLAYERS_BUTTON, 1800, 50)
    , _teamsButton(Constants::TextureId::BOTTOM_TEAMS_BUTTON, 1800, 50)
    , _arrowBetweenPlayersTeams(Constants::TextureId::BOTTOM_ARROW_RIGHT, 1800, 50)
    , _arrowUp(Constants::TextureId::BOTTOM_ARROW_UP, 1800, 50)
    , _arrowDown(Constants::TextureId::BOTTOM_ARROW_DOWN, 1800, 50)
    , _playerCount(Constants::FontId::STARCRAFT_FONT, "Players count :", 1800, 50)
{
    Json json = Json::fromFile("../../zappySettings.json");

    if (client._mapSize.x == 0 || client._mapSize.y == 0)
        client.getMapSize();
    _mapSize.x = client._mapSize.x;
    _mapSize.y = client._mapSize.y;

    _tileWidth = textureBase[Constants::TextureId::FLOOR1].getSize().x;
    _tileHeight = textureBase[Constants::TextureId::FLOOR1].getSize().y;
    _mouseWheelSensitivity = 100.f / json["graphicalSettings"]["mouseWheelSensitivity"].get<float>();
    _invertXAxis = json["graphicalSettings"]["invertXAxis"].get<bool>();
    _invertYAxis = json["graphicalSettings"]["invertYAxis"].get<bool>();

    buildTileMap();
    placeCamera(window);
    _cursor.updatePosition(window);

    // Test
    /*
    _players.emplace_back(0, 2, 98, 1);
    placeNewPlayer();
    _players.emplace_back(1, 2, 98, 2);
    placeNewPlayer();
    _players.emplace_back(2, 2, 98, 3);
    placeNewPlayer();
    _players.emplace_back(3, 2, 98, 4);
    placeNewPlayer();
    _players.emplace_back(0, 3, 98, 5);
    placeNewPlayer();
    _players.emplace_back(1, 3, 98, 6);
    _players.back().orientation = PlayerData::Orientation::EAST;
    placeNewPlayer();
    _players.emplace_back(2, 3, 98, 7);
    _players.back().orientation = PlayerData::Orientation::SOUTH;
    placeNewPlayer();
    _players.emplace_back(3, 3, 98, 8);
    _players.back().orientation = PlayerData::Orientation::WEST;
    placeNewPlayer();
    */

    // Creating interface.

    _displayWin.setCharacterSize(60);
    _displayWin.setInterfacePosition(
        window.getSize().x / 2 - _displayWin.getGlobalBounds().width / 2,
        window.getSize().y / 2 - _displayWin.getGlobalBounds().height / 2);

    _compass.setInterfacePosition(window.getSize().x / 2 - _compass.getTextureRect().width / 2, 10);
    _compassCursor.setInterfacePosition(window.getSize().x / 2 - _compassCursor.getTextureRect().width / 2, 50);

    _objectDescriptionPanel.setInterfacePosition(10, window.getSize().y / 6);
    _objectDescriptionPanel._textObjects.emplace_back(Constants::FontId::STARCRAFT_FONT);
    _objectDescriptionPanel._textObjects.back().pos.x = 15;
    _objectDescriptionPanel._textObjects.back().pos.y = 15;
    _objectDescriptionPanel._textObjects.back().setCharacterSize(17);
    _objectDescriptionPanel._textObjects.back().setFillColor({250, 0, 108});
    _objectDescriptionPanel._textObjects.emplace_back(Constants::FontId::STARCRAFT_FONT);
    _objectDescriptionPanel._textObjects.back().pos.x = 200;
    _objectDescriptionPanel._textObjects.back().pos.y = 15;
    _objectDescriptionPanel._textObjects.back().setCharacterSize(17);
    _objectDescriptionPanel._textObjects.back().setFillColor({250, 0, 108});
    _bottomBar.setInterfacePosition(window.getSize().x / 2, window.getSize().y - _bottomBar.getTextureRect().height / 2);
    _bottomBar.centerObject();
    _tvBackground.centerObject();
    _tvBackground.setInterfacePosition(155, window.getSize().y - _tvBackground.getTextureRect().height / 2);
    _face.centerObject();
    _face.setInterfacePosition(155, window.getSize().y - _face.getTextureRect().height / 2);

    _tvEffect.centerObject();
    _tvEffect.setInterfacePosition(155, window.getSize().y - _tvEffect.getTextureRect().height / 2);
    _tvEffect.setVisible(false);

    _timePanel.setInterfacePosition(window.getSize().x - _timePanel.getTextureRect().width - 5, 10);
    _timeText.setInterfacePosition(window.getSize().x - _timePanel.getTextureRect().width + 5, 49);
    _timeText._textObjects.emplace_back(Constants::FontId::STARCRAFT_FONT, "", 10, 10);
    _timeText._textObjects.back().setFillColor({242, 213, 22});
    _timeSetButton.setInterfacePosition(window.getSize().x - _timePanel.getTextureRect().width + 54, 107);

    int bx = 380;
    int by = window.getSize().y - 190;
    _teamsButton.setInterfacePosition(bx, by);
    _playersButton.setInterfacePosition(bx + 190, by);
    _arrowBetweenPlayersTeams.setInterfacePosition(bx + 130, by);
    _arrowUp.setInterfacePosition(bx, by + 60);
    _arrowDown.setInterfacePosition(bx, by + 110);

    _playersButton.setVisible(false);
    _arrowBetweenPlayersTeams.setVisible(false);

    _playerCount.setInterfacePosition(bx + 340, by + 5);

    focusCameraOn(&_tiles[0], window);

    updatePanelInfos();
    resetBottomBar();

    thread.reset(new std::thread([&]{
        while (!client.closed && !closed)
        {
            try {
                computeEvents(window, event, client);
            } catch (const std::exception & e) {
                std::cerr << "Compute Events Crash : " << e.what() << std::endl;
                exit(EXIT_FAILURE);
            }
            client.waitForParsed();
        }
    }));
}

Game::~Game()
{
    closed = true;
    thread->join();
}

int Game::compute(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client)
{
    static auto wheelStart = std::chrono::steady_clock::now();

    if (event.type == sf::Event::KeyReleased)
    {
        if (event.key.code == sf::Keyboard::A)
            rotate(Game::Direction::RIGHT, window);
        if (event.key.code == sf::Keyboard::E)
            rotate(Game::Direction::LEFT, window);
        if (event.key.code == sf::Keyboard::Z || event.key.code == sf::Keyboard::Up)
            moveCamera(window, Direction::UP);
        if (event.key.code == sf::Keyboard::Q || event.key.code == sf::Keyboard::Left)
            moveCamera(window, Direction::LEFT);
        if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)
            moveCamera(window, Direction::RIGHT);
        if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
            moveCamera(window, Direction::DOWN);

        if (event.key.code == sf::Keyboard::F1 || event.key.code == sf::Keyboard::F2)
            focusOnPlayer(window, event, client);
        if (event.key.code == sf::Keyboard::F3 || event.key.code == sf::Keyboard::F4)
            focusOnEgg(window, event, client);

        if (cameraTarget())
        {
            if (event.key.code == sf::Keyboard::Y)
                cameraTarget()->move(0, -_tileHeight, 1);
            if (event.key.code == sf::Keyboard::G)
                cameraTarget()->move(-_tileWidth, 0, 1);
            if (event.key.code == sf::Keyboard::H)
                cameraTarget()->move(0, _tileHeight, 1);
            if (event.key.code == sf::Keyboard::J)
                cameraTarget()->move(_tileWidth, 0, 1);
            if (event.key.code == sf::Keyboard::O)
                static_cast<Mob *>(cameraTarget())->startElevation();
            if (event.key.code == sf::Keyboard::P)
            {
                static_cast<Mob *>(cameraTarget())->stopElevation();
                static_cast<Mob *>(cameraTarget())->upLevel();
            }
            if (event.key.code == sf::Keyboard::M)
                static_cast<Mob *>(cameraTarget())->stopElevation();
        }
    }
    else if (event.type == sf::Event::MouseWheelScrolled)
    {
        auto end = std::chrono::steady_clock::now();
        auto elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(end - wheelStart).count();

        if (elapsedMs > _mouseWheelSensitivity)
        {
            if (event.key.shift)
            {
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
                {
                    if (event.mouseWheelScroll.delta > 0)
                        window.zoom(1.15);
                    if (event.mouseWheelScroll.delta < 0)
                        window.zoom(1.f / 1.15);
                }
            }
            wheelStart = std::chrono::steady_clock::now();
        }
    }
    _cursor.updatePosition(window);
    checkCursorHighlight();

    (event.type == sf::Event::MouseButtonPressed) ? _cursor.clickAnimation() : _cursor.noClickAnimation();

    if (_cursor.pointedObject != nullptr)
    {
        if (event.type == sf::Event::MouseButtonReleased)
        {
            if (event.mouseButton.button == sf::Mouse::Button::Left)
            {
                leftClickInteractions(window, event, client);
            }
            else if (event.mouseButton.button == sf::Mouse::Button::Right)
            {

            }
        }
    }
    writeInteractions(event, client);
    return EXIT_SUCCESS;
}

#include <cmath>

int Game::draw(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client)
{
    if (_mapSize.x == 0 || _mapSize.y == 0)
    {
        std::cerr << "Map size not received." << std::endl;
        return EXIT_FAILURE;
    }

    placeCamera(window);
    updatePanelInfos();

    _tvEffect.setVisible(_tvEffect.isAnimating());

    _background.animateBackground(20);

    window.draw(_background);

    /*
    try {
        computeEvents(window, event, client);
    } catch (const std::exception & e) {
        std::cerr << "Compute Events Crash : " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
    */

    checkCursorHighlight();

    static auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    auto elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

    if (elapsedSeconds >= (sqrt(_mapSize.x * _mapSize.y) / 2 + 1))
    {
        start = std::chrono::steady_clock::now();
        client.getEveryTilesContent();
    }

    for (auto & tile : _tiles)
        window.draw(tile);

    for (auto & object : _objects)
        window.draw(object);

    for (auto & egg : _eggs)
        window.draw(egg);

    for (auto & player : _players)
        window.draw(player);

    window.draw(_objectDescriptionPanel);

    window.draw(_compass);
    window.draw(_compassCursor);
    window.draw(_tvBackground);
    window.draw(_face);
    window.draw(_tvEffect);

    window.draw(_bottomBar);

    window.draw(_timePanel);
    window.draw(_timeText);
    window.draw(_timeSetButton);

    window.draw(_playersButton);
    window.draw(_teamsButton);
    window.draw(_arrowBetweenPlayersTeams);
    window.draw(_arrowUp);
    window.draw(_arrowDown);

    window.draw(*displayBar());

    window.draw(_playerCount);

    for (auto & interfaceObject : _interfaceObjects)
        window.draw(interfaceObject);

    for (auto & interfaceObject : _interfaceTextObjects)
        window.draw(interfaceObject);

    window.draw(_displayWin);

    window.draw(_cursor);
    checkEnd(window);
    return EXIT_SUCCESS;
}

void Game::checkCursorHighlight()
{
    if (_cursor.highlightObject(_timeSetButton))
        return;

    if (_cursor.highlightObject(_timeText))
        return;

    if (_cursor.highlightObject(_teamsButton))
        return;

    if (_cursor.highlightObject(_arrowUp))
        return;

    if (_cursor.highlightObject(_arrowDown))
        return;

    for (auto & button : *displayBar())
    {
        if (_cursor.highlightObject(button))
            return;
    }

    for (auto & object : _players)
    {
        if (_cursor.highlightObject(object))
            return;
    }

    for (auto & object : _eggs)
    {
        if (_cursor.highlightObject(object))
            return;
    }

    for (auto & object : _objects)
    {
        if (_cursor.highlightObject(object))
            return;
    }

    for (auto & object : _tiles)
    {
        if (_cursor.highlightObject(object))
            return;
    }

    _cursor.resetHighlight();
}

void Game::focusOnEgg(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client)
{
    if (!_eggs.empty())
    {
        for (auto & egg : _eggs)
        {
            if (_cameraTarget == egg)
                goto switchEgg;
        }
        focusCameraOn(&_eggs[0], window);
        return;

        switchEgg:

        if (event.key.code == sf::Keyboard::F3)
        {
            if (_cameraTarget == _eggs[0])
                focusCameraOn(&_eggs.back(), window);
            else
            {
                for (size_t i = 0; i < _eggs.size(); ++i)
                {
                    if (_cameraTarget == _eggs[i])
                    {
                        focusCameraOn(&_eggs[i-1], window);
                        break;
                    }
                }
            }
        }
        else
        {
            if (_cameraTarget == _eggs.back())
                focusCameraOn(&_eggs[0], window);
            else
            {
                for (size_t i = 0; i < _eggs.size() - 1; ++i)
                {
                    if (_cameraTarget == _eggs[i])
                    {
                        focusCameraOn(&_eggs[i+1], window);
                        break;
                    }
                }
            }
        }
    }
}

void Game::focusOnPlayer(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client)
{
    if (!_players.empty())
    {
        for (auto & player : _players)
        {
            if (_cameraTarget == player)
                goto switchPlayer;
        }
        focusCameraOn(&_players[0], window);
        return;

        switchPlayer:

        if (event.key.code == sf::Keyboard::F1)
        {
            if (_cameraTarget == _players[0])
                focusCameraOn(&_players.back(), window);
            else
            {
                for (size_t i = 0; i < _players.size(); ++i)
                {
                    if (_cameraTarget == _players[i])
                    {
                        focusCameraOn(&_players[i-1], window);
                        break;
                    }
                }
            }
        }
        else
        {
            if (_cameraTarget == _players.back())
                focusCameraOn(&_players[0], window);
            else
            {
                for (size_t i = 0; i < _players.size() - 1; ++i)
                {
                    if (_cameraTarget == _players[i])
                    {
                        focusCameraOn(&_players[i+1], window);
                        break;
                    }
                }
            }
        }
    }
}

void Game::updatePanelInfos()
{
    // Object Description Panel.
    gameMutex.lock(LINE());

    _objectDescriptionPanel.setVisible(true);

    if (!cameraTarget())
    {
        gameMutex.unlock();
        return;
    }

    try
    {

    std::string textToDisplay;
    std::string sTextToDisplay;

    if (cameraTarget()->objectIdentity == Object::ObjectIdentity::Egg
     || cameraTarget()->objectIdentity == Object::ObjectIdentity::Mob
     || cameraTarget()->objectIdentity == Object::ObjectIdentity::Floor)
    {
        textToDisplay += "Target Informations :\n\n\n";
        textToDisplay += "Id : " + ((cameraTarget()->objectIdentity != Object::ObjectIdentity::Floor) ? std::to_string((static_cast<Mob *>(cameraTarget()))->id) : "Floor Tile") + "\n";
        textToDisplay += "Position : [";
        textToDisplay += std::to_string(cameraTarget()->pos.x) + ", " + std::to_string(cameraTarget()->pos.y) + "]\n";
        sTextToDisplay += "\n\n\n\n";
    }

    if (cameraTarget()->objectIdentity == Object::ObjectIdentity::Egg
     || cameraTarget()->objectIdentity == Object::ObjectIdentity::Mob)
    {
        auto ptr = static_cast<Mob *>(cameraTarget());
        textToDisplay += "Team : " + ptr->teamName + "\n";
        textToDisplay += "Level : " + std::to_string(ptr->level) + "\n";
        textToDisplay += "Incanting : " + std::string(((ptr->isIncanting) ? "Yes" : "No")) + "\n";
        textToDisplay += "Orientation : ";
        textToDisplay += PlayerData::orientationToString(ptr->orientation);
        textToDisplay += "\n";
        sTextToDisplay += "\n\n\n\n";
    }

    if (cameraTarget()->objectIdentity == Object::ObjectIdentity::Egg
     || cameraTarget()->objectIdentity == Object::ObjectIdentity::Mob
     || cameraTarget()->objectIdentity == Object::ObjectIdentity::Floor)
    {
        textToDisplay += "\n\n\nInventory :\n\n\n";
        sTextToDisplay += "\n\n\n\n\n\n\n";

        if (cameraTarget()->objectIdentity == Object::ObjectIdentity::Floor)
        {
            auto ptr = static_cast<Floor *>(cameraTarget());
            textToDisplay += "Food :\n";
            textToDisplay += "Linemate :\n";
            textToDisplay += "Deraumere :\n";
            textToDisplay += "Sibur :\n";
            textToDisplay += "Mendiane :\n";
            textToDisplay += "Phiras :\n";
            textToDisplay += "Thystmane :\n";
            sTextToDisplay += std::to_string(ptr->inventory.food)      + "\n";
            sTextToDisplay += std::to_string(ptr->inventory.linemate)  + "\n";
            sTextToDisplay += std::to_string(ptr->inventory.deraumere) + "\n";
            sTextToDisplay += std::to_string(ptr->inventory.sibur)     + "\n";
            sTextToDisplay += std::to_string(ptr->inventory.mendiane)  + "\n";
            sTextToDisplay += std::to_string(ptr->inventory.phiras)    + "\n";
            sTextToDisplay += std::to_string(ptr->inventory.thystmane) + "\n";
        }
        else
        {
            auto ptr = static_cast<Mob *>(cameraTarget());
            textToDisplay += "Food :\n";
            textToDisplay += "Linemate :\n";
            textToDisplay += "Deraumere :\n";
            textToDisplay += "Sibur :\n";
            textToDisplay += "Mendiane :\n";
            textToDisplay += "Phiras :\n";
            textToDisplay += "Thystmane :\n";
            sTextToDisplay += std::to_string(ptr->inventory.food)      + "\n";
            sTextToDisplay += std::to_string(ptr->inventory.linemate)  + "\n";
            sTextToDisplay += std::to_string(ptr->inventory.deraumere) + "\n";
            sTextToDisplay += std::to_string(ptr->inventory.sibur)     + "\n";
            sTextToDisplay += std::to_string(ptr->inventory.mendiane)  + "\n";
            sTextToDisplay += std::to_string(ptr->inventory.phiras)    + "\n";
            sTextToDisplay += std::to_string(ptr->inventory.thystmane) + "\n";
        }
    }

    if (cameraTarget()->objectIdentity == Object::ObjectIdentity::Egg
     || cameraTarget()->objectIdentity == Object::ObjectIdentity::Mob)
    {
        auto ptr = static_cast<Mob *>(cameraTarget());
        textToDisplay += "\nLast Broadcast Msg :\n\n";
        for (size_t i = 0; i < ptr->broadcastMessage.size(); i += 25)
        {
            textToDisplay += ptr->broadcastMessage.substr(i, 25) + "\n";
        }
    }

    _objectDescriptionPanel._textObjects[0].setString(textToDisplay);
    _objectDescriptionPanel._textObjects[1].setString(sTextToDisplay);
    if (textToDisplay.empty())
        _objectDescriptionPanel.setVisible(false);

    } catch (const std::exception & e)
    {
        std::cerr << "WTF!!! : " << e.what() << std::endl;
    }

    // Bottom bar.

    if (cameraTarget()->textureId != _currentTvTextureId)
    {
        if ((_currentTvTextureId == Constants::TextureId::FLOOR1 && cameraTarget()->textureId == Constants::TextureId::FLOOR2)
         || (_currentTvTextureId == Constants::TextureId::FLOOR2 && cameraTarget()->textureId == Constants::TextureId::FLOOR1))
        {
            gameMutex.unlock();
            return;
        }

        static const std::map<Constants::TextureId, std::tuple<Constants::TextureId, Constants::MusicId>> panelTextures = {
            {Constants::TextureId::FLOOR1, {Constants::TextureId::FACE_FLOOR, Constants::MusicId::TOTAL_SOUND}},
            {Constants::TextureId::FLOOR2, {Constants::TextureId::FACE_FLOOR, Constants::MusicId::TOTAL_SOUND}},
            {Constants::TextureId::COCOON, {Constants::TextureId::FACE_COCOON, Constants::MusicId::SOUND_COCOON}},
            {Constants::TextureId::LARVA, {Constants::TextureId::FACE_LARVA, Constants::MusicId::SOUND_LARVA}},
            {Constants::TextureId::DRONE, {Constants::TextureId::FACE_DRONE, Constants::MusicId::SOUND_DRONE}},
            {Constants::TextureId::ZERGLING, {Constants::TextureId::FACE_ZERGLING, Constants::MusicId::SOUND_ZERGLING}},
            {Constants::TextureId::BANELING, {Constants::TextureId::FACE_BANELING, Constants::MusicId::SOUND_BANELING}},
            {Constants::TextureId::ROACH, {Constants::TextureId::FACE_ROACH, Constants::MusicId::SOUND_ROACH}},
            {Constants::TextureId::HYDRALISK, {Constants::TextureId::FACE_HYDRALISK, Constants::MusicId::SOUND_HYDRALISK}},
            {Constants::TextureId::QUEEN, {Constants::TextureId::FACE_QUEEN, Constants::MusicId::SOUND_QUEEN}},
            {Constants::TextureId::ULTRALISK, {Constants::TextureId::FACE_ULTRALISK, Constants::MusicId::SOUND_ULTRALISK}}
        };

        try
        {
            Constants::TextureId foundId = std::get<0>(panelTextures.at(cameraTarget()->textureId));
            _tvEffect.setVisible(true);
            _tvEffect.removeActualAnimations();
            _tvEffect.animateQueue(Object::AnimateOptions::EndsOnLastFrame, 0.3, 0);
            _tvEffect.animateQueue(Object::AnimateOptions::EndsOnLastFrame
                                 | Object::AnimateOptions::Reverse, 0.3, 0);
            _face.changeTexture(foundId, 0.5);
            if (std::get<1>(panelTextures.at(cameraTarget()->textureId)) != Constants::MusicId::TOTAL_SOUND)
                musicBase[std::get<1>(panelTextures.at(cameraTarget()->textureId))].play();
            _currentTvTextureId = cameraTarget()->textureId;
        }
        catch (const std::exception & e)
        {
            std::cerr << e.what() << std::endl;
        }
    }

    gameMutex.unlock();
}

void Game::leftClickInteractions(ZappyRenderWindow & window, sf::Event & event, GraphicalClient & client)
{
    timeTextFocused = (_cursor.pointedObject == &_timeText);

    if (bottomBarInteractions(window, event, client)) {}
    else if (_cursor.pointedObject == &_timeSetButton)
    {
        client.setTimeUnit(std::stoi(_timeText._textObjects[0].getString().toWideString()));
        client.getTimeUnit();
    }
    else if (_cursor.pointedObject == &_timeText) {}
    else
    {
        focusCameraOn(_cursor.pointedObject, window);
        checkCursorHighlight();
    }
}

void Game::writeInteractions(sf::Event & event, GraphicalClient & client)
{
    if (!timeTextFocused)
        return;

    auto character = getChar(event);

    if (!character.empty())
    {
        if (_timeText._textObjects[0].getString().getSize() <= 6)
            _timeText._textObjects[0].setString(_timeText._textObjects[0].getString() + character);
    }
    else
    {
        if (event.type == sf::Event::KeyReleased)
        {
            if (_timeText._textObjects[0].getString().getSize() != 0)
                if (event.key.code == sf::Keyboard::Delete || event.key.code == sf::Keyboard::BackSpace)
                    _timeText._textObjects[0].setString(_timeText._textObjects[0].getString().substring(0, _timeText._textObjects[0].getString().getSize() - 1));

            if (event.key.code == sf::Keyboard::Return)
                client.setTimeUnit(std::stoi(_timeText._textObjects[0].getString().toAnsiString()));
            event.type = sf::Event::Count;
        }
    }
}

std::string Game::getChar(sf::Event & event)
{
    std::string c;
    const std::map<sf::Keyboard::Key, KVector<std::string>> chars = {
        {sf::Keyboard::Key::Num0, {{""}, {'0'}}},
        {sf::Keyboard::Key::Num1, {{""}, {'1'}}},
        {sf::Keyboard::Key::Num2, {{""}, {'2'}}},
        {sf::Keyboard::Key::Num3, {{""}, {'3'}}},
        {sf::Keyboard::Key::Num4, {{""}, {'4'}}},
        {sf::Keyboard::Key::Num5, {{""}, {'5'}}},
        {sf::Keyboard::Key::Num6, {{""}, {'6'}}},
        {sf::Keyboard::Key::Num7, {{""}, {'7'}}},
        {sf::Keyboard::Key::Num8, {{""}, {'8'}}},
        {sf::Keyboard::Key::Num9, {{""}, {'9'}}},
        {sf::Keyboard::Key::Numpad0, {{'0'}, {'0'}}},
        {sf::Keyboard::Key::Numpad1, {{'1'}, {'1'}}},
        {sf::Keyboard::Key::Numpad2, {{'2'}, {'2'}}},
        {sf::Keyboard::Key::Numpad3, {{'3'}, {'3'}}},
        {sf::Keyboard::Key::Numpad4, {{'4'}, {'4'}}},
        {sf::Keyboard::Key::Numpad5, {{'5'}, {'5'}}},
        {sf::Keyboard::Key::Numpad6, {{'6'}, {'6'}}},
        {sf::Keyboard::Key::Numpad7, {{'7'}, {'7'}}},
        {sf::Keyboard::Key::Numpad8, {{'8'}, {'8'}}},
        {sf::Keyboard::Key::Numpad9, {{'9'}, {'9'}}}
    };

    if (event.type == sf::Event::KeyReleased)
    {
        try
        {
            int index = (event.key.shift) ? 1 : 0;
            c = chars.at(event.key.code)[index];
        }
        catch(const std::exception& e) {}
    }
    return c;
}

void Game::checkEnd(ZappyRenderWindow & window)
{
    static bool set = false;
    static std::chrono::steady_clock::time_point start;

    if (set)
    {
        auto end = std::chrono::steady_clock::now();
        auto elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

        if (elapsedSeconds >= 5)
            window.close();
    }
    if (_gameEnded && !set)
    {
        _displayWin.setString("The winner is :\n" + _winningTeam + " !");
        set = true;
        start = std::chrono::steady_clock::now();
    }
}