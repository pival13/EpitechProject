/*
** EPITECH PROJECT, 2020
** B-CPP-501-NCY-5-1-rtype-etienne.miltgen
** File description:
** RoomManager
*/

#ifndef ROOMMANAGER_HPP_
#define ROOMMANAGER_HPP_

#include "../ReadMessage.hpp"
#include "../WriteMessage.hpp"
#include "../UdpGestion.hpp"

class RoomManager {
    public:
        RoomManager(std::shared_ptr<UdpGestion> & udpGestion);
        ~RoomManager();
        WriteMessage sendAllRoom();
        void createRoom(ReadMessage & readBuffer,
            boost::shared_ptr<Participant> participant,
            WriteMessage & answer);
        void joinRoom(ReadMessage & readBuffer,
            boost::shared_ptr<Participant> participant,
            WriteMessage & answer);
        void leaveRoom(ReadMessage & readBuffer,
            boost::shared_ptr<Participant> participant,
            WriteMessage & answer);

    private:
        std::shared_ptr<UdpGestion> & __udpGestion;

    private:
        void makeAnswer(Rtype::Rfc::TcpCode code, WriteMessage & answer, bool pos);
        void makeAnswer(unsigned short port, boost::uuids::uuid uuid, WriteMessage & answer);
        get_room_t makeAnswer(boost::shared_ptr<UdpServer> udp);

};

#endif /* !ROOMMANAGER_HPP_ */
