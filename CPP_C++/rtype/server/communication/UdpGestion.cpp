/*
** EPITECH PROJECT, 2020
** B-CPP-501-NCY-5-1-rtype-etienne.miltgen
** File description:
** UdpGestion
*/

#include "UdpGestion.hpp"

UdpGestion::UdpGestion(boost::asio::io_context & ioc,
        boost::asio::io_context::strand & strand)
    : __ioc(ioc),
    __strand(strand)
{
}

UdpGestion::~UdpGestion()
{
}

/**
 * @brief Create a game'es room.
 * 
 * @param player Player who create the room.
 * @param room Contains all information about the room.
 * @param port Port on wich the game will be started.
 */
void UdpGestion::createRoom(boost::shared_ptr<Participant> player,
        create_room_t room, boost::uuids::uuid roomUuid, int port)
{
    try {
        boost::shared_ptr<UdpServer> udp =
                UdpServer::create(player, roomUuid, room, port, this->__ioc, this->__strand);
        this->__udps.push_back(udp);
    } catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * @brief Add a player to the specified room.
 * 
 * @param player Player to add.
 * @param uuid UUoid of the room.
 * @return true If the player has been added with success.
 * @return false If the room doesn't food.
 */
bool UdpGestion::addPlayer(boost::shared_ptr<Participant> player,
        boost::uuids::uuid uuid)
{
    for (auto & udp: this->__udps) {
        if (udp->getUuid() == uuid &&
                udp->getNumberOfPlayer() < udp->getPlace()) {
            udp->addPlayer(player);
            return true;
        }
    }
    return false;
}

/**
 * @brief Delete a player from a room.
 * 
 * @param roomUuid The room's uuid.
 * @param player The client's will be deleted.
 * @return true if the client has been deleted.
 * @return false if the client can't be deleted.
 */
bool UdpGestion::deletePlayer(boost::uuids::uuid roomUuid,
        boost::shared_ptr<Participant> & player) {
    for (std::deque<boost::shared_ptr<UdpServer>>::iterator it = this->__udps.begin()
            ; it != this->__udps.end(); ++it) {
        if ((*it)->getUuid() == roomUuid) {
            (*it)->deletePlayer(player);
            if ((*it)->getNumberOfPlayer() == 0)
                this->__udps.erase(it);
            return true;
        }
    }
    return false;
}

std::deque<boost::shared_ptr<UdpServer>> UdpGestion::getAllServer() const
{
    return this->__udps;
}

boost::shared_ptr<UdpServer> UdpGestion::getServer(
        boost::uuids::uuid roomUuid) const
{
    for (auto & udp : this->__udps) {
        if (roomUuid == udp->getUuid())
            return udp;
    }
    return nullptr;
}
