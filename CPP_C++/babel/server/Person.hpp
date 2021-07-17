/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** Person
*/

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <iostream>
#include <deque>

#include "ReadMessage.hpp"
#include "WriteMessage.hpp"
#include "ChatRoom.hpp"
#include "Login.hpp"
#include "Signup.hpp"
#include "NewStatus.hpp"
#include "AddFriend.hpp"
#include "DeleteFriend.hpp"
#include "Disconnect.hpp"
#include "Message.hpp"
#include "GetContactMessage.hpp"
#include "Call.hpp"

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
            ChatRoom& room, const std::string & dbPath);
        std::string getParticipantMail();
        void WriteStatusBuffer(WriteMessage writeMessage);
        tcp::socket& socket();
        std::string getIp();
        short getPort();
        void start();
        void setUuid(boost::uuids::uuid uuid);
        boost::uuids::uuid getUUid() const;

    private:
        Person(boost::asio::io_context& ioc,
            boost::asio::io_context::strand& strand,
            ChatRoom& room, const std::string & dbPath);
        void runCommand();
        void doWrite();
        void doRead();
        void close();

    private:
        tcp::socket m_socket;
        ReadMessage readMessage;
        std::deque<WriteMessage> writeBuffer;
        std::string message;
        boost::asio::streambuf buffer;
        boost::asio::io_context& m_context;
        boost::asio::io_context::strand& m_strand;
        boost::uuids::uuid m_uuid;
        ChatRoom& m_room;
        std::string m_mail;
        std::string m_ip;
        short m_port;
        const std::string & m_dbPath;
};

#endif /* !CHAT_SESSION_HPP_ */
