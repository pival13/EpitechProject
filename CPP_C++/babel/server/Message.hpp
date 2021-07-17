/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** Message
*/

#ifndef MESSAGE_HPP_
#define MESSAGE_HPP_

#include "ReadMessage.hpp"
#include "WriteMessage.hpp"
#include "MySqlite.hpp"
#include "ChatRoom.hpp"
#include <regex>
#include "../libs/message_struct.h"
#include "../libs/mail_struct.h"

class Message {
    public:
        Message(ReadMessage& readMessage,
            WriteMessage& writeMessage, const std::string & mail, ChatRoom &room,
            const std::string & dbPath);
        ~Message();
        void getAnswer();

    private:
        bool checkUser(const std::string & mail);
        void messageFailed(const std::string & mail);
        void messageFailed();
        void messageSuccess(const std::string & mail);
        void sendMessage(message_t messageOrigin);
        void saveMessage(message_t message);
        bool checkReceiver(const std::string & mail);

    private:
        WriteMessage& m_writeMessage;
        ReadMessage& m_readMessage;
        const std::string &m_mail;
        ChatRoom &m_room;
        const std::string & m_dbPath;
};

#endif /* !MESSAGE_HPP_ */
