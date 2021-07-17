/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** NewStatus
*/

#ifndef NEWSTATUS_HPP_
#define NEWSTATUS_HPP_

#include "ReadMessage.hpp"
#include "WriteMessage.hpp"
#include "MySqlite.hpp"
#include "../libs/status_struct.h"
#include "ChatRoom.hpp"

class NewStatus {
    public:
        NewStatus(ReadMessage &ReadMessage, ChatRoom& room,
                type_t status, const std::string &mail, const std::string & dbPath);
        void updateStatus(status_t status, const std::string &mail);
        void updateStatus(status_t status, int id);
        void notificationStatus();
        ~NewStatus();
        void getAnswer();

    private:
        void createMessage(WriteMessage &message);

    private:
        type_t m_type;
        const std::string &m_mail;
        ReadMessage &m_readMessage;
        ChatRoom &m_room;
        status_t m_status;
        const std::string & m_dbPath;

};

#endif /* !NEWSTATUS_HPP_ */
