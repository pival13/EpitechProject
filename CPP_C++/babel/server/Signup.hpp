/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** Signup
*/

#ifndef SIGNUP_HPP_
#define SIGNUP_HPP_

#include "ReadMessage.hpp"
#include "WriteMessage.hpp"
#include "MySqlite.hpp"
#include "../libs/get_contact_struct.h"
#include "NewStatus.hpp"

class Signup {
    public:
        Signup(ReadMessage& ReadMessage,
                WriteMessage& WriteMessage, std::string & mail, short & port,
                const std::string & dbPath);
        void getAnswer();
        void SignUpFailed();
        void SignUpSuccess();
        ~Signup();

    private:
        WriteMessage& m_writeMessage;
        ReadMessage& m_readMessage;
        std::string & mail;
        short & m_port;
        const std::string & m_dbPath;

    private:
        sqltable executeRequest(signup_t singup);
};

#endif /* !SIGNUP_HPP_ */
