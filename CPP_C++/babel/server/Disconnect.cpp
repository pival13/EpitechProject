/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** Disconnect
*/

#include "Disconnect.hpp"

Disconnect::Disconnect(ReadMessage &ReadMessage, const std::string &mail,
        ChatRoom& room, const std::string & dbPath)
    : m_readMessage(ReadMessage),
    m_mail(mail),
    m_room(room),
    m_dbPath(dbPath)
{
}

Disconnect::~Disconnect()
{
}

/**
 * @brief Disconenect the current client of the
 * server and update client's status inside the db.
 * 
 */
void Disconnect::getAnswer()
{
    NewStatus status(this->m_readMessage, this->m_room, NEW_STATUS, this->m_mail, this->m_dbPath);
    status.updateStatus(OFFLINE, this->m_mail);
    status.notificationStatus();
}
