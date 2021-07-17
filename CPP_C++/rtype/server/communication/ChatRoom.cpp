/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** ChatRoom
*/

#include "ChatRoom.hpp"

ChatRoom::ChatRoom()
{
}

ChatRoom::~ChatRoom()
{
}

/**
 * @brief Add the client at the room.
 * 
 * @param participant Client to add.
 */
void ChatRoom::enter(boost::shared_ptr<Participant> participant)
{
    this->m_participants.insert(participant);
}

/**
 * @brief Delete the client from the room.
 * 
 * @param participant Client to be deleted.
 */
void ChatRoom::leave(boost::shared_ptr<Participant> participant)
{
    this->m_participants.erase(participant);
}

