/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** AddFriend
*/

#ifndef ADDFRIEND_HPP_
#define ADDFRIEND_HPP_

#include "ReadMessage.hpp"
#include "WriteMessage.hpp"
#include "MySqlite.hpp"
#include "../libs/add_friend_struct.h"

class AddFriend {
    public:
        AddFriend(ReadMessage& readMessage,WriteMessage& writeMessage,
                const std::string &mail, const std::string & dbPath);
        ~AddFriend();
        void getAnswer();

    private:
        bool checkUser(const std::string& mail);
        int getUserId();
        void AddFriendFailed();
        void AddFriendFailed(const std::string & fiendMail);
        void AddFriendSuccess(const std::string &mail);
        sqltable getInformationAboutContact(const std::string &mail);

    private:
        ReadMessage& m_readMessage;
        WriteMessage& m_writeMessage;
        const std::string & m_mail;
        const std::string & m_dbPath;
};

#endif /* !ADDFRIEND_HPP_ */
