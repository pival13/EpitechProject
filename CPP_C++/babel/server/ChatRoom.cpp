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
 * @brief Create call with two Users.
 * 
 * @param firstUser 
 * @param secondUser 
 * @return boost::uuids::uuid The uuid of the call.
 */
boost::uuids::uuid ChatRoom::createCall(boost::shared_ptr<Participant> firstUser,
        boost::shared_ptr<Participant> secondUser)
{
    std::set<boost::shared_ptr<Participant>> tmp;
    boost::uuids::uuid uuid = boost::uuids::random_generator()();

    tmp.insert(firstUser);
    tmp.insert(secondUser);
    this->m_calls.insert(std::pair<boost::uuids::uuid, std::set<boost::shared_ptr<Participant>>>(uuid, tmp));
    return uuid;
}

/**
 * @brief Add user to the specific call
 * 
 * @param uuid Uuid of the call.
 * @param participant The client to add at the call.
 */
void ChatRoom::addUserToACall(boost::uuids::uuid uuid, boost::shared_ptr<Participant> participant)
{
    this->m_calls.at(uuid).insert(participant);
}

/**
 * @brief Add user to the specific call
 * 
 * @param uuid Uuid of the call.
 * @param participant The client will be deleted from the call.
 */
void ChatRoom::deleteUserToACall(boost::uuids::uuid uuid, const boost::shared_ptr<Participant> & participant)
{
    this->m_calls.at(uuid).erase(participant);
    if (this->m_calls.at(uuid).empty())
        this->m_calls.erase(uuid);
}

std::set<boost::shared_ptr<Participant>> &ChatRoom::getParticipantCall(boost::uuids::uuid uuid)
{
    for (auto & t : this->m_calls)
        if (t.first == uuid)
            return t.second;
    throw std::runtime_error("No call find");
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

/**
 * @brief Get the client that matches with the mail address.
 * 
 * @param mail Client's mail address.
 * @return boost::shared_ptr<Participant> Clients who matches with the mail adress.
 */
boost::shared_ptr<Participant> ChatRoom::getParticipant(const std::string & mail)
{
    for(auto f : this->m_participants) {
        if (std::strcmp(f->getParticipantMail().data(), mail.data()) == 0) {
            return f;
        }
    }
    return nullptr;
}
