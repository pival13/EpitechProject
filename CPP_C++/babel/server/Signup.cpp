/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** Signup
*/

#include "Signup.hpp"

Signup::Signup(ReadMessage& ReadMessage,
        WriteMessage& WriteMessage, std::string & mail, short & port,
        const std::string & dbPath)
    : m_readMessage(ReadMessage),
    m_writeMessage(WriteMessage),
    mail(mail),
    m_port(port),
    m_dbPath(dbPath)
{
}

Signup::~Signup()
{
}

void Signup::SignUpSuccess()
{
    get_contact_t getContact;
    std::string tmp;

    getContact.header.size = sizeof(get_contact_message_t) - sizeof(header_t);
    getContact.header.func = GET_CONTACT;
    std::memset(getContact.mail, 0, LOGIN_LENGTH);
    std::memset(getContact.username, 0, LOGIN_LENGTH);
    getContact.status = (status_t)0;
    this->m_writeMessage.addData(&getContact, sizeof(get_contact_t));
}

void Signup::SignUpFailed()
{
    header_t header;

    header.size = 0;
    header.func = SIGN_UP_ERROR;
    this->m_writeMessage.setData(&header, sizeof(header_t));
}

sqltable Signup::executeRequest(signup_t signup)
{
    MySqlite sql(this->m_dbPath);
    return sql.excuteSelect("select password from users where mail=\"" +
            std::string(signup.mail) + "\";");
}

void Signup::getAnswer()
{
    std::cout << "je suis dans le sign up" << std::endl;
    signup_t signup = this->m_readMessage.getSignUp();
    std::string sqlString = std::string(
            "insert into users (username, mail, password, status) values('") +
            signup.username + "','" + signup.mail + "','" +
            signup.password + "','" + std::to_string(ONLINE) + "');";
    sqltable result;

    if (!this->mail.empty())
        return SignUpFailed();
    try {
        result = executeRequest(signup);
    } catch (const std::exception &err) {
        std::cerr << err.what() << std::endl;
        return;
    }
    if (!result.empty()) {
        SignUpFailed();
    } else {
        MySqlite sql(this->m_dbPath);
        if (sql.excuteInsert(sqlString)) {
            SignUpSuccess();
            this->mail = std::string(signup.mail);
            this->m_port = signup.port;
        } else {
            SignUpFailed();
        }
    }
}
