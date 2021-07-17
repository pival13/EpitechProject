/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** Login
*/

#ifndef LOGIN_HPP_
#define LOGIN_HPP_

#include <vector>

#include "ReadMessage.hpp"
#include "WriteMessage.hpp"
#include "MySqlite.hpp"

class Login {
    public:
        Login(ReadMessage & readMessage,
                WriteMessage & writeMesage, std::string & mail,
                short & port, const std::string & dbPath);
        ~Login();
        void getAnswer();

    private:
        void loginSucess(const sqltable &request);
        void loginFailed();

    private:
        ReadMessage& m_readMessage;
        WriteMessage& m_writeMessage;
        const std::string & m_dbPath;
        std::string m_mail;
        std::string m_username;
        std::string m_dbPassword;
        std::string & mail;
        short & m_port;
};

#endif /* !LOGIN_HPP_ */
