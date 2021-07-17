/*
** EPITECH PROJECT, 2020
** RType_2020
** File description:
** Menu
*/

#include "Menu.hpp"
#include"my.hpp"

Menu::Menu()
: AScene(MENU)
{
    sf::Texture *textureMenuBack = new sf::Texture();
    sf::Texture *textureTitle = new sf::Texture();
    sf::Texture *texturePlay = new sf::Texture();
    sf::Texture *textureExit = new sf::Texture();
    sf::Texture *textureOptions = new sf::Texture();
    sf::Texture *texturePlayIn = new sf::Texture();
    sf::Texture *textureExitIn = new sf::Texture();
    sf::Texture *textureOptionsIn = new sf::Texture();
    sf::Texture *textureCross = new sf::Texture();
    sf::Texture *textureCrossIn = new sf::Texture();
    sf::Texture *textureBlurSetting = new sf::Texture();
    sf::Texture *textureVolume = new sf::Texture();
    sf::Texture *texturePlus = new sf::Texture();
    sf::Texture *textureMoins = new sf::Texture();
    sf::Texture *textureMoinsIn = new sf::Texture();
    sf::Texture *texturePlusIn = new sf::Texture();
    sf::Texture *textureEdit = new sf::Texture();
    sf::Texture *textureEditIn = new sf::Texture();
    sf::Texture *textureBlur = new sf::Texture();
    sf::Texture *textureRoomCadre = new sf::Texture();

    sf::Texture *textureCreate = new sf::Texture();
    sf::Texture *textureCreateIn = new sf::Texture();
    sf::Texture *textureJoin = new sf::Texture();
    sf::Texture *textureJoinIn = new sf::Texture();

    sf::Texture *textureNameRoom = new sf::Texture();
    sf::Texture *textureNameRoomIn = new sf::Texture();
    sf::Texture *textureNameRoomClick = new sf::Texture();
    sf::Texture *textureNameRoomIndisp = new sf::Texture();



    std::string dir = __FILE__;
    dir = dir.substr(0, dir.find_last_of("\\/"));
    if (textureRoomCadre->loadFromFile(dir + "/../img_src/Croom.png") == false) exit(EXIT_FAILURE);
    if (textureMenuBack->loadFromFile(dir + "/../img_src/parallax.png") == false) exit(EXIT_FAILURE);
    if (textureTitle->loadFromFile(dir + "/../img_src/prototype.png") == false) exit(EXIT_FAILURE);
    if (texturePlay->loadFromFile(dir + "/../img_src/play.png") == false) exit(EXIT_FAILURE);
    if (texturePlayIn->loadFromFile(dir + "/../img_src/playIn.png") == false) exit(EXIT_FAILURE);
    if (textureExit->loadFromFile(dir + "/../img_src/exit.png") == false) exit(EXIT_FAILURE);
    if (textureExitIn->loadFromFile(dir + "/../img_src/exitIn.png") == false) exit(EXIT_FAILURE);
    if (textureOptions->loadFromFile(dir + "/../img_src/options.png") == false) exit(EXIT_FAILURE);
    if (textureOptionsIn->loadFromFile(dir + "/../img_src/optionsIn.png") == false) exit(EXIT_FAILURE);
    if (textureCross->loadFromFile(dir + "/../img_src/cross.png") == false) exit(EXIT_FAILURE);
    if (textureCrossIn->loadFromFile(dir + "/../img_src/crossIn.png") == false) exit(EXIT_FAILURE);
    if (textureBlurSetting->loadFromFile(dir + "/../img_src/blursettings.png") == false) exit(EXIT_FAILURE);
    if (textureVolume->loadFromFile(dir + "/../img_src/volume.png") == false) exit(EXIT_FAILURE);
    if (textureMoins->loadFromFile(dir + "/../img_src/moins.png") == false) exit(EXIT_FAILURE);
    if (texturePlus->loadFromFile(dir + "/../img_src/plus.png") == false) exit(EXIT_FAILURE);
    if (texturePlusIn->loadFromFile(dir + "/../img_src/plusIn.png") == false) exit(EXIT_FAILURE);
    if (textureMoinsIn->loadFromFile(dir + "/../img_src/moinsIn.png") == false) exit(EXIT_FAILURE);
    if (textureEdit->loadFromFile(dir + "/../img_src/edit.png") == false) exit(EXIT_FAILURE);
    if (textureEditIn->loadFromFile(dir + "/../img_src/editIn.png") == false) exit(EXIT_FAILURE);
    if (textureBlur->loadFromFile(dir + "/../img_src/blurmenu.png") == false) exit(EXIT_FAILURE);

    if (textureCreateIn->loadFromFile(dir + "/../img_src/CreateRoomIn.png") == false) exit(EXIT_FAILURE);
    if (textureCreate->loadFromFile(dir + "/../img_src/CreateRoom.png") == false) exit(EXIT_FAILURE);
    if (textureJoinIn->loadFromFile(dir + "/../img_src/PlayRoomIn.png") == false) exit(EXIT_FAILURE);
    if (textureJoin->loadFromFile(dir + "/../img_src/PlayRoom.png") == false) exit(EXIT_FAILURE);

    if (textureNameRoom->loadFromFile(dir + "/../img_src/RoomName.png") == false) exit(EXIT_FAILURE);
    if (textureNameRoomIn->loadFromFile(dir + "/../img_src/RoomNameIn.png") == false) exit(EXIT_FAILURE);
    if (textureNameRoomClick->loadFromFile(dir + "/../img_src/RoomNameClick.png") == false) exit(EXIT_FAILURE);
    if (textureNameRoomIndisp->loadFromFile(dir + "/../img_src/RoomNameIndisp.png") == false) exit(EXIT_FAILURE);


    //////// BACKGROUND ///////////
    _bg = sf::Sprite(*textureMenuBack, sf::IntRect(0, 0, 1920, 1080));
    _bgCpy = sf::Sprite(*textureMenuBack, sf::IntRect(0, 0, 1920, 1080));
    _bg.setPosition(0, 0);
    _bgCpy.setPosition(1920, 0);

    _settingBlurForm = sf::Sprite(*textureBlurSetting);
    _RoomCadre = sf::Sprite(*textureRoomCadre);
    _volume = sf::Sprite(*textureVolume);
    _volume.setScale(0.8f, 0.8f);

    _blurform = sf::Sprite(*textureBlur);

    //////// TITLE //////////////
    _title = new sf::Sprite(*textureTitle);
    _titleSize = sf::Vector2f(773.0f, 282.0f);

    ////////////// BUTTONS ///////////////
    _buttonPlay = sf::Sprite(*texturePlay);
    _buttonPlayIn = sf::Sprite(*texturePlayIn);
    _buttonExit = sf::Sprite(*textureExit);
    _buttonExitIn = sf::Sprite(*textureExitIn);
    _buttonOptions = sf::Sprite(*textureOptions);
    _buttonOptionsIn = sf::Sprite(*textureOptionsIn);
    _buttonCross = sf::Sprite(*textureCross);
    _buttonCrossIn = sf::Sprite(*textureCrossIn);
    _buttonPlus = sf::Sprite(*texturePlus);
    _buttonMoins = sf::Sprite(*textureMoins);
    _buttonPlusIn = sf::Sprite(*texturePlusIn);
    _buttonMoinsIn = sf::Sprite(*textureMoinsIn);
    _buttonEdit = sf::Sprite(*textureEdit);
    _buttonEditIn = sf::Sprite(*textureEditIn);
    _buttonCreate = sf::Sprite(*textureCreate);
    _buttonCreateIn = sf::Sprite(*textureCreateIn);
    _buttonJoin = sf::Sprite(*textureJoin);
    _buttonJoinIn = sf::Sprite(*textureJoinIn);
    _buttonNameRoom = sf::Sprite(*textureNameRoom);
    _buttonNameRoomIn = sf::Sprite(*textureNameRoomIn);
    _buttonNameRoomClick = sf::Sprite(*textureNameRoomClick);
    _buttonNameRoomIndisp = sf::Sprite(*textureNameRoomIndisp);

    
    _isScaling = false;
    _isSettings = false;
    _isRoom = false;
    _nbr = 0;
}

Menu::~Menu()
{
}

void Menu::drawRooms(game_t *gm, sf::RenderWindow *window)
{
    for (size_t i = 0; i < gm->rooms.size(); ++i) {
        sf::Sprite *s = &_buttonNameRoom;
        if (gm->roomUuid == gm->rooms[i].uuid)
            s = &_buttonNameRoomClick;
        else if (gm->rooms[i].numberOfPlayer == gm->rooms[i].place)
            s = &_buttonNameRoomIndisp;
        else if (mouseInArea(window->mapPixelToCoords(sf::Mouse::getPosition(*window)), sf::FloatRect((1920 / 2) - (577 / 2), float((1080 / 2) - (69 / 2) + 49 + 70 * i), 577, 69))) {
            s = &_buttonNameRoomIn;
            if (mouseIsPressed(gm->event))
                gm->roomUuid = gm->rooms[i].uuid;
        }
        s->setPosition((1920 / 2) - (577 / 2), (1080 / 2) - (69 / 2) + 49 + 70 * float(i));
        window->draw(*s);

        sf::Text t(std::string(gm->rooms[i].name), *gm->fontMusic);
        t.setPosition((1920 / 2) - (577 / 2) + 50, (1080 / 2) - (69 / 2) + 49 + 70 * float(i) + 10);
        window->draw(t);

        t = sf::Text(std::to_string(gm->rooms[i].numberOfPlayer) + " / " + std::to_string(gm->rooms[i].place), *gm->fontMusic);
        t.setPosition((1920 / 2) - (577 / 2) + 500, (1080 / 2) - (69 / 2) + 49 + 70 * float(i) + 10);
        window->draw(t);
    }
}

void Menu::drawGame(game_t *gm, sf::RenderWindow *window)
{
    window->clear();
    window->draw(_bg);
    window->draw(_bgCpy);
    window->draw(*_title);
    if (!_isScaling && _nbr != 0 && !_isSettings && !_isRoom) {
        window->draw(_blurform);
        if (!_inPlay) window->draw(_buttonPlay);
        else window->draw(_buttonPlayIn);
        if (!_inEdit) window->draw(_buttonEdit);
        else window->draw(_buttonEditIn);
        if (!_inOptions) window->draw(_buttonOptions);
        else window->draw(_buttonOptionsIn);
        if (!_inExit) window->draw(_buttonExit);
        else window->draw(_buttonExitIn);
    } else if (_isSettings) {
        window->draw(_settingBlurForm);
        if (!_inCross) window->draw(_buttonCross);
        else window->draw(_buttonCrossIn);
        window->draw(_volume);
        if (!_inMoins) window->draw(_buttonMoins);
        else window->draw(_buttonMoinsIn);
        if (!_inPlus) window->draw(_buttonPlus);
        else  window->draw(_buttonPlusIn);
    }
    else if (_isRoom) {
        window->draw(_settingBlurForm);
        window->draw(_RoomCadre);
        if (!_inCross) window->draw(_buttonCross);
        else window->draw(_buttonCrossIn);

        if (!_inCreate) window->draw(_buttonCreate);
        else window->draw(_buttonCreateIn);
        if (!_inJoin) window->draw(_buttonJoin);
        else  window->draw(_buttonJoinIn);

        drawRooms(gm, window);
    }
}

void Menu::updateGame(game_t *gm, sf::RenderWindow *)
{
    _time = gm->clock.getElapsedTime();

    if (_time.asSeconds() > 2.0f && !_isScaling && gm->a <= 45) _isScaling = true;
    if (_isScaling) {
        if (_time.asSeconds() > 0.04f) {
            _title->setScale(1.0f - (0.0065f * gm->a), 1.0f - (0.0065f * gm->a));
            _titleSize.x -= 5.2f;
            _titleSize.y -= 1.8f;
            _nbr += 7;
            gm->clock.restart();
            gm->a++;
        }
        if (gm->a > 45) _isScaling = false;
    } else {
        _blurform.setPosition((1920 / 2) - (500 / 2), 300);
        _buttonPlay.setPosition((1920 / 2) - (500 / 2), 350);
        _buttonPlayIn.setPosition((1920 / 2) - (500 / 2), 350);
        _buttonEdit.setPosition((1920 / 2) - (500 / 2), 500);
        _buttonEditIn.setPosition((1920 / 2) - (500 / 2), 500);
        _buttonOptions.setPosition((1920 / 2) - (500 / 2), 650);
        _buttonOptionsIn.setPosition((1920 / 2) - (500 / 2), 650);
        _buttonExit.setPosition((1920 / 2) - (500 / 2), 800);
        _buttonExitIn.setPosition((1920 / 2) - (500 / 2), 800);
        
        _settingBlurForm.setPosition((1920 / 2) - (700 / 2), (1080 / 2) - (533 / 2) + 150);
        _RoomCadre.setPosition((1920 / 2) - (700 / 2), (1080 / 2) - (500 / 2) + 200);
        _buttonCross.setPosition(1258, (1080 / 2) - (533 / 2) + 150);
        _buttonCrossIn.setPosition(1258, (1080 / 2) - (533 / 2) + 150);
        _buttonMoins.setPosition(700, 550);
        _buttonPlus.setPosition(1150, 550);
        _buttonMoinsIn.setPosition(700, 550);
        _buttonPlusIn.setPosition(1150, 550);
        _volume.setPosition(900, 560);
        _buttonJoin.setPosition((1920 / 2) - (202 / 2) + 200, (1080 / 2) - (51 / 2) + 425);
        _buttonJoinIn.setPosition((1920 / 2) - (202 / 2) + 200, (1080 / 2) - (51 / 2) + 425);
        _buttonCreate.setPosition((1920 / 2) - (202 / 2) - 200, (1080 / 2) - (51 / 2) + 425);
        _buttonCreateIn.setPosition((1920 / 2) - (202 / 2) -200, (1080 / 2) - (51 / 2) + 425);
    }
    if (gm->parallax.getElapsedTime().asMilliseconds() > 10) {
        if (_bg.getTextureRect().left > 1920) {
            _bg.setPosition(_bg.getPosition().x - 1, 0);
            _bgCpy.setPosition(_bgCpy.getPosition().x - 1, 0);
            if (_bgCpy.getPosition().x < 1) {
                _bg.setTextureRect(sf::IntRect(0, 0, 1920, 1080));
                _bg.setPosition(0, 0);
                _bgCpy.setPosition(1920, 0);
            }
        }
        else _bg.setTextureRect(sf::IntRect(_bg.getTextureRect().left + 1, 0, 1920, 1080));
        gm->parallax.restart();
    }
    _title->setPosition(1920 / 2 - _titleSize.x / 2, (1080 / 2) - (_titleSize.y / 2) - _nbr - 100);
}

void Menu::getEvents(game_t *gm, sf::RenderWindow *window)
{
    sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

    _inPlay = false;
    _inOptions = false;
    _inExit = false;
    _inCross = false;
    _inPlus = false;
    _inMoins = false;
    _inEdit = false;
    _inCreate = false;
    _inJoin = false;
    _inNameRoom = false;
    if (mouseInButton(mousePos, _buttonPlay) && !_isSettings && !_isRoom) {
        _inPlay = true;
        if (mouseIsPressed(gm->event)) {
            //gm->nextPage = GAME;
            gm->wantRoom = true;
            _isRoom = true;
        }
    } else if (mouseInButton(mousePos, _buttonEdit) && !_isSettings && !_isRoom) {
        _inEdit = true;
        if (mouseIsPressed(gm->event)) {}
     } else if (mouseInButton(mousePos, _buttonOptions) && !_isSettings && !_isRoom) {
        _inOptions = true;
        if (mouseIsPressed(gm->event)) _isSettings = true;
    } else if (mouseInButton(mousePos, _buttonExit) && !_isSettings && !_isRoom) {
        _inExit = true;
        if (mouseIsPressed(gm->event)) gm->nextPage = END;
    }
    if (_isSettings && mouseInButton(mousePos, _buttonCross)) {
        _inCross = true;
        if (mouseIsPressed(gm->event)) _isSettings = false;
        
    }
    if (_isRoom && mouseInButton(mousePos, _buttonCross)) {
        _inCross = true;
        if (mouseIsPressed(gm->event)) _isRoom = false;
        
    }

    if (_isSettings && mouseInButton(mousePos, _buttonPlus)) {
        _inPlus = true;
        if (mouseIsPressed(gm->event)) {
            float volume = gm->music->getVolume();
            if (volume <= 100.0f) {
                volume += 10.0f;
                if (volume > 100.0f) volume = 100.0f;
            }
            gm->music->setVolume(volume);
        }
    }
    if (_isSettings && mouseInButton(mousePos, _buttonMoins)) {
        _inMoins = true;
        if (mouseIsPressed(gm->event)) {
            float volume = gm->music->getVolume();
            if (volume >= 0.0f) {
                volume -= 10.0f;
                if (volume < 0.0f) volume = 0.0f;
            }
            gm->music->setVolume(volume);
        }
    }

    if (_isRoom && mouseInButton(mousePos, _buttonJoin)) {
        _inJoin = true;
        if (mouseIsPressed(gm->event)) {
            gm->joinRoom = true;
        }
    }

    if (_isRoom && mouseInButton(mousePos, _buttonCreate)) {
        _inCreate = true;
        if (mouseIsPressed(gm->event)) {
            gm->createRoom = true;
        }
    }
}