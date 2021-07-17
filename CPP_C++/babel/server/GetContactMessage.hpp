/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** GetMessageContact
*/

#ifndef GETCONTACTMESSAGE_HPP_
#define GETCONTACTMESSAGE_HPP_

#include "ReadMessage.hpp"
#include "WriteMessage.hpp"
#include "MySqlite.hpp"

class GetContactMessage {
    public:
        GetContactMessage(ReadMessage &readMessage,
                WriteMessage &writeMessage, const std::string &mail,
                const std::string & dbPath);
        ~GetContactMessage();
        void getAnswer();

    private:
        bool checkUser(const std::string & mail);
        void getContactMessageFailed();
        sqltable getAllMessage(const std::string &receiver, int number);
        void sendContactMessage(const std::string &receiver, int number);

    private:
        ReadMessage &m_readMessage;
        WriteMessage &m_writeMessage;
        const std::string &m_mail;
        const std::string &m_dbPath;
};

#endif /* !GETCONTACTMESSAGE_HPP_ */
