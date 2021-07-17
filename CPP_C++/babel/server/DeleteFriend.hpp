/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** DeleteFriend
*/

#ifndef DELETEFRIEND_HPP_
#define DELETEFRIEND_HPP_

#include "MySqlite.hpp"
#include "ReadMessage.hpp"
#include "WriteMessage.hpp"

class DeleteFriend {
    public:
        DeleteFriend(ReadMessage& readMessage,
                WriteMessage& writeMessage, const std::string & mail,
                const std::string & dbPath);
        ~DeleteFriend();
        void getAnswer();

    private:
        bool checkUser(const std::string & mail);
        void deleteFriendSuccess(const std::string &mail);
        void deleteFriendFailed(const std::string &mail);
        void deleteFriendFailed();
        int getUserId();

    private:
        ReadMessage& m_readMessage;
        WriteMessage& m_writeMessage;
        const std::string &m_mail;
        const std::string & m_dbPath;
};

#endif /* !DELETEFRIEND_HPP_ */
