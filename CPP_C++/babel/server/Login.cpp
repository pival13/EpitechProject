/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** Login
*/

#include "Login.hpp"

Login::Login(ReadMessage &readMessage,
        WriteMessage &writeMessage, std::string & mail, short & port,
        const std::string & dbPath)
    : m_readMessage(readMessage),
    m_writeMessage(writeMessage),
    mail(mail),
    m_port(port),
    m_dbPath(dbPath)
{
}

Login::~Login()
{
}

void Login::loginFailed()
{
    header_t header;

    header.size = 0;
    header.func = LOGIN_ERROR;
    this->m_writeMessage.setData(&header, sizeof(header_t));
}

void Login::loginSucess(const sqltable &request)
{
    get_contact_t getContact;

    getContact.header.size = sizeof(get_contact_t) - sizeof(header_t);
    getContact.header.func = GET_CONTACT;
    std::memset(getContact.mail, 0, LOGIN_LENGTH);
    std::memset(getContact.username, 0, LOGIN_LENGTH);
    std::memcpy(getContact.mail, this->mail.data(), this->mail.size());
    std::memcpy(getContact.username, this->m_username.data(), this->m_username.size());
    getContact.status = ONLINE;
    this->m_writeMessage.setData(&getContact, sizeof(get_contact_t));
    if (!request.empty()) {
        for (int i = 0; i < request.at("mail").size(); ++i) {
            std::memset(getContact.mail, 0, LOGIN_LENGTH);
            std::memset(getContact.username, 0, LOGIN_LENGTH);
            std::memcpy(getContact.mail, request.at("mail").at(i).data(), request.at("mail").at(i).size());
            std::memcpy(getContact.username, request.at("username").at(i).data(), request.at("username").at(i).size());
            getContact.status = (status_t)std::stoi(request.at("status").at(i));
            this->m_writeMessage.addData(&getContact, sizeof(get_contact_t));
        }
    }
    std::memset(getContact.mail, 0, LOGIN_LENGTH);
    std::memset(getContact.username, 0, LOGIN_LENGTH);
    getContact.status = OFFLINE;
    this->m_writeMessage.addData(&getContact, sizeof(get_contact_t));
}

void Login::getAnswer()
{
    login_t login = this->m_readMessage.getLogin();
    sqltable result;
    std::string request = R"(
            SELECT friend.mail, friend.username, friend.status
            FROM contacts
            JOIN users client ON contacts.UserId=client._rowid_
            JOIN users friend ON contacts.email=friend.mail
            WHERE client.mail=')" + std::string(login.mail) + "';";

    if (login.mail == NULL || strlen(login.mail) == 0 ||
            login.password == NULL || strlen(login.password) == 0
            || !this->mail.empty()) {
        loginFailed();
        return;
    }
    MySqlite sql(this->m_dbPath);
    result = sql.excuteSelect("select password, username from users where mail=\"" +
            std::string(login.mail) + "\";");
    if (!result.empty()) {
        this->m_dbPassword = result.at("password").at(0);
        this->m_username = result.at("username").at(0);
    }
    if (!this->m_dbPassword.empty() &&
            this->m_dbPassword == std::string(login.password) ) {
        result = sql.excuteSelect(request);
        this->mail = std::string(login.mail);
        this->m_port = login.port;
        loginSucess(result);
    } else {
        loginFailed();
    }
}
