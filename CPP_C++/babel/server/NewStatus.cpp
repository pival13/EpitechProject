/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** NewStatus
*/

#include "NewStatus.hpp"

NewStatus::NewStatus(ReadMessage &readMessage, ChatRoom &room,
        type_t type, const std::string &mail, const std::string & dbPath)
    : m_readMessage(readMessage),
    m_room(room),
    m_type(type),
    m_mail(mail),
    m_dbPath(dbPath)
{
}

NewStatus::~NewStatus()
{
}

void NewStatus::createMessage(WriteMessage &message)
{

    status_changed_t status;

    status.header.size = sizeof(status_changed_t) - sizeof(header_t);
    status.header.func = STATUS_CHANGED;
    std::memset(status.mail, 0, LOGIN_LENGTH);
    std::memcpy(status.mail, this->m_mail.data(), this->m_mail.size());
    status.status = this->m_status;
    message.setData(&status, sizeof(status_changed_t));
}

void NewStatus::notificationStatus()
{
    MySqlite sql(this->m_dbPath);
    WriteMessage message;
    std::string request = R"( SELECT friend.mail, friend.username, friend.status
                            FROM contacts
                            JOIN users client ON contacts.UserId=client._rowid_
                            JOIN users friend ON contacts.email=friend.mail
                            WHERE client.mail=")" + this->m_mail + "\"" +
                            " AND friend.status=" + std::to_string(ONLINE);
    boost::shared_ptr<Participant> tmp;

    createMessage(message);
    sqltable result = sql.excuteSelect(request);
    if (result.empty())
        return;
    for (int i = 0; i < result.at("mail").size(); ++i) {
        tmp = this->m_room.getParticipant(result.at("mail").at(i));
        if (tmp != nullptr) {
            tmp->WriteStatusBuffer(message);
        }
    }
}

void NewStatus::getAnswer()
{
    new_status_t status = this->m_readMessage.getNewStatus();

    try {
        updateStatus(status.status, this->m_mail);
    } catch (const std::exception & err) {
        std::cerr << err.what() << std::endl;
    }
    if (this->m_type != SIGN_UP)
        notificationStatus();
}

void NewStatus::updateStatus(status_t status, const std::string &mail)
{
    MySqlite sql(this->m_dbPath);
    std::string request =
            "UPDATE users SET status=" + std::to_string(status) +
            " WHERE mail=\"" + mail + "\";";

    if (!sql.excuteInsert(request))
        throw std::runtime_error("Update status has failed");
    else
        this->m_status = status;
}

void NewStatus::updateStatus(status_t status, int id)
{
    MySqlite sql(this->m_dbPath);
    std::string request =
            "UPDATE users SET status=" + std::to_string(status) +
            " WHERE _rowid_=\"" + std::to_string(id) + "\";";

    if (!sql.excuteInsert(request))
        throw std::runtime_error("Update status has failed");
    else
        this->m_status = status;
}
