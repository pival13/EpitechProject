/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** GetMessageContact
*/

#include "GetContactMessage.hpp"

GetContactMessage::GetContactMessage(ReadMessage &readMessage,
        WriteMessage &writeMessage, const std::string &mail,
        const std::string & dbPath)
    : m_readMessage(readMessage),
    m_writeMessage(writeMessage),
    m_mail(mail),
    m_dbPath(dbPath)
{
}

GetContactMessage::~GetContactMessage()
{
}

bool GetContactMessage::checkUser(const std::string & mail)
{
    MySqlite sql(this->m_dbPath);
    std::string selectRequest = "select username from users where mail='"
            + mail + "';";
    sqltable result;

    result = sql.excuteSelect(selectRequest);
    if (result.empty())
        return false;
    return true;
}

void GetContactMessage::getContactMessageFailed()
{
    header_t header;

    header.size = 0;
    header.func = GET_CONTACT_MESSAGE_FAILED;
    this->m_writeMessage.setData(&header, sizeof(header_t));
}

sqltable GetContactMessage::getAllMessage(const std::string &receiver, int number)
{
    MySqlite sql(this->m_dbPath);
    std::string request = "SELECT Contain, Receiver, timestamp, Emitter, CASE Emitter WHEN '" + this->m_mail + "' " +
        "THEN 1 ELSE 0 END AS Emitself FROM messages WHERE Emitter IN ('" + this->m_mail + "','" + receiver + "') " +
        "AND Receiver IN ('" + this->m_mail + "','" + receiver + "') " +
        "ORDER BY timestamp DESC LIMIT " + std::to_string(number);

    return sql.excuteSelect(request);
}


void GetContactMessage::sendContactMessage(const std::string & receiverMail, int number)
{
    get_contact_message_answer_t answer;
    sqltable result = getAllMessage(receiverMail, number);
    int start = number - 25;

    answer.header.func = GET_CONTACT_MESSAGE_ANSWER;
    answer.header.size = sizeof(get_contact_message_answer_t) - sizeof(header_t);
    if (!result.empty()) {
        for (int i = 0; i < result.at("Receiver").size(); ++i) {
            if (i >= start) {
                answer.timestamp = std::stoull(result.at("timestamp").at(i).data());
                std::memset(answer.message, 0, MESSAGE_LENGTH);
                std::memcpy(answer.message, result.at("Contain").at(i).data(),
                        result.at("Contain").at(i).size());
                std::memset(answer.receiver, 0, LOGIN_LENGTH);
                std::memcpy(answer.receiver, result.at("Receiver").at(i).data(),
                        result.at("Receiver").at(i).size());
                std::memset(answer.sender, 0, LOGIN_LENGTH);
                std::memcpy(answer.sender, result.at("Emitter").at(i).data(),
                        result.at("Emitter").at(i).size());
                if (i == start)
                    this->m_writeMessage.setData(&answer, sizeof(get_contact_message_answer_t));
                else
                    this->m_writeMessage.addData(&answer, sizeof(get_contact_message_answer_t));
            }
        }
    }
    answer.timestamp = 0;
    std::memset(answer.message, 0, MESSAGE_LENGTH);
    std::memset(answer.receiver, 0, LOGIN_LENGTH);
    std::memset(answer.sender, 0, LOGIN_LENGTH);
    if (!result.empty()) {
        this->m_writeMessage.addData(&answer, sizeof(get_contact_message_answer_t));
    } else {
        this->m_writeMessage.setData(&answer, sizeof(get_contact_message_answer_t));
    }
}

void GetContactMessage::getAnswer()
{
    get_contact_message_t getContactMessage = this->m_readMessage.getContactMessage();

    if (getContactMessage.mail == NULL || getContactMessage.number < 25
            || this->m_mail.empty()) {
        getContactMessageFailed();
        return;
    }
    if (!checkUser(std::string(getContactMessage.mail))) {
        getContactMessageFailed();
    } else {
        sendContactMessage(std::string(getContactMessage.mail), getContactMessage.number);
    }
}