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

class ChatRoom {
    public:
        ChatRoom();
        ~ChatRoom();
        void enter(boost::shared_ptr<Participant>);
        void leave(boost::shared_ptr<Participant>);

    private:
        std::set<boost::shared_ptr<Participant>> m_participants;
};

#endif /* !CHATROOM_HPP_ */
