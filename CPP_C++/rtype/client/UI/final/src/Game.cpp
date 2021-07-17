/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** ClientGame
*/

#include "Game.hpp"

ClientGame::ClientGame()
: AScene(GAME), inputs({0, 0, false, false})
{
    t.loadFromFile(std::string(__FILE__).substr(0, std::string(__FILE__).find_last_of("\\/")) + "/../img_src/bgingame.png");
    bg.setTexture(t);
    isRunning = true;
}

ClientGame::~ClientGame()
{
    isRunning = false;
    PointerHandler::materials.clear();
    if (threadUdp.joinable()) threadUdp.join();
}

void ClientGame::getEvents(game_t *gm, sf::RenderWindow *)
{
    if (gm->event.type == sf::Event::EventType::KeyPressed) {
        if (gm->event.key.code == sf::Keyboard::Key::Left || gm->event.key.code == sf::Keyboard::Key::Q)
            inputs.moveX = -100;
        else if (gm->event.key.code == sf::Keyboard::Key::Right || gm->event.key.code == sf::Keyboard::Key::D)
            inputs.moveX = 100;
        else if (gm->event.key.code == sf::Keyboard::Key::Up || gm->event.key.code == sf::Keyboard::Key::Z)
            inputs.moveY = -100;
        else if (gm->event.key.code == sf::Keyboard::Key::Down || gm->event.key.code == sf::Keyboard::Key::S)
            inputs.moveY = 100;
        else if (gm->event.key.code == sf::Keyboard::Key::Space)
            inputs.isShooting = true;
        else if (gm->event.key.code == sf::Keyboard::Key::N)
            inputs.useBomb = true;
        else if (gm->event.key.code == sf::Keyboard::Key::Escape)
            gm->nextPage = MENU;
    } else if (gm->event.type == sf::Event::EventType::KeyReleased) {
        if (inputs.moveX < 0 && (gm->event.key.code == sf::Keyboard::Key::Left || gm->event.key.code == sf::Keyboard::Key::Q))
            inputs.moveX = 0;
        else if (inputs.moveX > 0 && (gm->event.key.code == sf::Keyboard::Key::Right || gm->event.key.code == sf::Keyboard::Key::D))
            inputs.moveX = 0;
        else if (inputs.moveY < 0 && (gm->event.key.code == sf::Keyboard::Key::Up || gm->event.key.code == sf::Keyboard::Key::Z))
            inputs.moveY = 0;
        else if (inputs.moveY > 0 && (gm->event.key.code == sf::Keyboard::Key::Down || gm->event.key.code == sf::Keyboard::Key::S))
            inputs.moveY = 0;
        else if (gm->event.key.code == sf::Keyboard::Key::Space)
            inputs.isShooting = false;
        else if (gm->event.key.code == sf::Keyboard::Key::N)
            inputs.useBomb = false;
    }
}

void ClientGame::updateGame(game_t *gm, sf::RenderWindow *)
{
    if (!threadUdp.joinable())
        threadUdp = std::thread([this, gm]() {
            while (isRunning) {
                if (!gm->core.isUdpRunning()) {
                    gm->core.initUdp();
                } else {
                    if (gm->core.udpAction(std::vector<uint8_t>((uint8_t*)&inputs, (uint8_t*)&inputs + sizeof(inputs))))
                        gm->core.getUpdate();
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
            gm->core.leaveRoom(gm->roomUuid.data());
            gm->roomUuid.clear();
        });

    auto datas = gm->core.getUdpUpdate();
    outputs = std::vector<RTypeNetworkObject>((RTypeNetworkObject*)datas.data(), (RTypeNetworkObject*)datas.data() + datas.size() / sizeof(RTypeNetworkObject));
}

void ClientGame::drawGame(game_t *gm, sf::RenderWindow *w)
{
    w->clear(sf::Color::White);

    bg.setPosition(float(-(gm->parallax.getElapsedTime().asMilliseconds() / 10) % bg.getTexture()->getSize().x), 0);
    w->draw(bg);
    bg.move(-float(bg.getTexture()->getSize().x), 0);
    w->draw(bg);

    for (RTypeNetworkObject &object : outputs) {
        if (!listObjects.count(object.uuid)) {
            try {
                switch (object.type) {
                    case RTypeObjectType::ObjectPlayer:
                        listObjects.emplace(object.uuid, RTypeFactory::createPlayer("RTPlayer"));
                        listObjects[object.uuid]->getSprite();
                        listObjects[object.uuid]->setColor(playerColor.at(object.player.playerId));
                        break;
                    case RTypeObjectType::ObjectEnemy:
                        listObjects.emplace(object.uuid, RTypeFactory::createEnemy(enemyName.at(object.enemy.enemyType)));
                        break;
                    case RTypeObjectType::ObjectMissile:
                        listObjects.emplace(object.uuid, RTypeFactory::createMissile(missileName.at(object.missileType)));
                        break;
                    case RTypeObjectType::ObjectObstacle:
                        listObjects.emplace(object.uuid, RTypeFactory::createObstacle("DestroyableObstacle"));
                        break;
                }
            } catch (const std::exception &e) {
                std::cerr << "[Client] Failed to create an object: " << e.what() << std::endl;
                continue;
            }
        }
        Drawable *obj = listObjects[object.uuid].get();
        obj->setPosition({double(object.posx-RType::border), double(object.posy-RType::border), 0});
        obj->setRotation({0, 0, double(object.angle)});
        obj->setScale({double(object.scalex)/100.0, double(object.scaley)/100.0, 1});
        w->draw(obj->getSprite());

        //auto b = obj->getColliders().front()->getTransform().getGlobalBounds();
        //r.setSize({float(b[3]-b[0]), float(b[4]-b[1])});
        //r.setPosition(float(b[0]), float(b[1]));
        //w._window.draw(r);
    }
}
