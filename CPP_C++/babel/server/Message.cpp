/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** Message
*/

#include "Message.hpp"

Message::Message(ReadMessage& readMessage,
WriteMessage& writeMesage, const std::string & mail, ChatRoom &room,
        const std::string & dbPath)
    : m_readMessage(readMessage),
    m_writeMessage(writeMesage),
    m_mail(mail),
    m_room(room),
    m_dbPath(dbPath)
{
}

Message::~Message()
{
}

bool Message::checkUser(const std::string & mail)
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

void Message::messageFailed(const std::string & destMail)
{
    mail_t mail;

    mail.header.size = 0;
    mail.header.func = MESSAGE_FAILED;
    std::memset(mail.mail, 0, LOGIN_LENGTH);
    std::memcpy(mail.mail, destMail.data(), destMail.size());
    this->m_writeMessage.setData(&mail, sizeof(mail_t));
}

void Message::messageFailed()
{
    header_t header;

    header.size = 0;
    header.func = MESSAGE_FAILED;
    this->m_writeMessage.setData(&header, sizeof(header_t));
}

void Message::messageSuccess(const std::string & destMail)
{
    mail_t mail;

    mail.header.size = sizeof(mail_t) - sizeof(header_t);
    mail.header.func = MESSAGE_SUCCESS;
    std::memset(mail.mail, 0, LOGIN_LENGTH);
    std::memcpy(mail.mail, destMail.data(), destMail.size());
    this->m_writeMessage.setData(&mail, sizeof(mail_t));
}

bool Message::checkReceiver(const std::string &mail)
{
    MySqlite sql(this->m_dbPath);
    sqltable result;
    std::string request = "select username from users where status="
            + std::to_string(ONLINE) + " AND mail='" + mail + "';";

    result = sql.excuteSelect(request);
    if (result.empty())
        return false;
    return true;
}

void Message::sendMessage(message_t messageOrigin)
{
    message_t message;
    WriteMessage desMessage;
    boost::shared_ptr<Participant> tmp;

    message.header.size = sizeof(message_t) - sizeof(header_t);
    message.header.func = MESSAGE;
    std::memset(message.mail, 0, LOGIN_LENGTH);
    std::memcpy(message.mail, this->m_mail.data(), LOGIN_LENGTH);
    std::memset(message.message, 0, LOGIN_LENGTH);
    std::memcpy(message.message, messageOrigin.message, LOGIN_LENGTH);
    message.timestamp = messageOrigin.timestamp;
    desMessage.setData(&message, sizeof(message_t));

    tmp = this->m_room.getParticipant(std::string(messageOrigin.mail));
    if (tmp != nullptr)
        tmp->WriteStatusBuffer(desMessage);
}

void Message::saveMessage(message_t message)
{
    MySqlite sql(this->m_dbPath);
    std::string request = R"(INSERT INTO messages
            ('Receiver', 'Emitter', 'Contain', 'timestamp') values (')" +
            std::string(message.mail) + "','" + this->m_mail + "','" + std::regex_replace(message.message, std::regex("'"), "''") +
            "'," + std::to_string(message.timestamp) + ");";

    if (sql.excuteInsert(request) == false) {
        std::cerr << request << std::endl;
        throw std::runtime_error("Save message request has failed");
    }
}

void Message::getAnswer()
{
    message_t message = this->m_readMessage.getMessage();

    if (message.mail == NULL || message.message == NULL
            || message.timestamp == 0 || this->m_mail.empty()) {
        messageFailed();
        return;
    }
    if (checkUser(message.mail)) {
        messageSuccess(std::string(message.mail));
        try {
            saveMessage(message);
        } catch (std::exception & err) {
            std::cerr << err.what() << std::endl;
            messageFailed(message.mail);
            return;
        }
        if (checkReceiver(std::string(message.mail))) {
            sendMessage(message);
        }
    } else {
        messageFailed(message.mail);
        return;
    }
}
