/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** Disconnect
*/

#ifndef DISCONNECT_HPP_
#define DISCONNECT_HPP_

#include "MySqlite.hpp"
#include "NewStatus.hpp"
#include "ReadMessage.hpp"

class Disconnect {
    public:
        Disconnect(ReadMessage &ReadMessage, const std::string &mail,
                ChatRoom& room, const std::string & dbPath);
        ~Disconnect();
        void getAnswer();

    private:
        ReadMessage& m_readMessage;
        const std::string &m_mail;
        ChatRoom& m_room;
        const std::string & m_dbPath;
};

#endif /* !DISCONNECT_HPP_ */
