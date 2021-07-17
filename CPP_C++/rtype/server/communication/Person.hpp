/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** Person
*/

#include <iostream>
#include <deque>

#include "WriteMessage.hpp"
#include "ReadMessage.hpp"
#include "ChatRoom.hpp"
#include "UdpGestion.hpp"
#include "action/RoomManager.hpp"
#include "include/player.hpp"

#include <memory>

#ifndef CHAT_SESSION_HPP_
#define CHAT_SESSION_HPP_

using boost::asio::ip::tcp;

class Person : public Participant,
                public boost::enable_shared_from_this<Person> {

    public:
        ~Person();
        typedef boost::shared_ptr<Person> pointer;
        static pointer create(boost::asio::io_context& ioc,
                boost::asio::io_context::strand& strand,
                ChatRoom& room, std::shared_ptr<RoomManager> & roomManager,
                std::shared_ptr<UdpGestion> & udpGestion);
        tcp::socket& socket();
        void start();
        const boost::uuids::uuid getUuid() const;
        const std::string getName() const;

    private:
        Person(boost::asio::io_context& ioc,
                boost::asio::io_context::strand& strand,
                ChatRoom& room, std::shared_ptr<RoomManager> & roomManager,
                std::shared_ptr<UdpGestion> & udpGestion);
        void runCommand();
        void doWrite();
        void doRead();
        void sendPlayerUuid();

    private:
        tcp::socket __socket;
        ReadMessage __readMessage;
        std::deque<WriteMessage> __writeBuffer;
        boost::asio::streambuf __readBuffer;
        boost::asio::io_context& __context;
        boost::asio::io_context::strand& __strand;
        boost::uuids::uuid __uuid;
        std::string __name;
        ChatRoom & __room;
        std::shared_ptr<RoomManager> & __roomManager;
        std::shared_ptr<UdpGestion> & __udpGestion;

};

#endif /* !CHAT_SESSION_HPP_ */
