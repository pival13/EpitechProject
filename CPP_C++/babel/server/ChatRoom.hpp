/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** ChatRoom
*/

#ifndef CHATROOM_HPP_
#define CHATROOM_HPP_

#include "Participant.hpp"
#include <iostream>
#include <memory>
#include <set>
#include <boost/asio.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

class ChatRoom {
    public:
        ChatRoom();
        ~ChatRoom();
        void enter(boost::shared_ptr<Participant>);
        void leave(boost::shared_ptr<Participant>);
        boost::shared_ptr<Participant> getParticipant(const std::string & mail);
        boost::uuids::uuid createCall(boost::shared_ptr<Participant> firstUser,
                boost::shared_ptr<Participant> secondUser);
        void addUserToACall(boost::uuids::uuid, boost::shared_ptr<Participant>);
        void deleteUserToACall(boost::uuids::uuid, const boost::shared_ptr<Participant> &);
        std::set<boost::shared_ptr<Participant>> &getParticipantCall(boost::uuids::uuid uuid);

    private:
        std::set<boost::shared_ptr<Participant>> m_participants;
        std::map<boost::uuids::uuid, std::set<boost::shared_ptr<Participant>>> m_calls;
};

#endif /* !CHATROOM_HPP_ */
