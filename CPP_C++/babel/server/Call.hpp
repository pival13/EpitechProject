/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** Call
*/

#ifndef CALL_HPP_
#define CALL_HPP_

#include "ReadMessage.hpp"
#include "WriteMessage.hpp"
#include "ChatRoom.hpp"

class Call {
    public:
        Call(ReadMessage & readMessage, const std::string & ip,
                const short & port, ChatRoom & chatRoom,
                const std::string & mail, boost::uuids::uuid & callUuid);
        ~Call();
        void sendAnswer(type_t type);
        void sendRequest();
        void leftCall();
        void addParticipant(boost::uuids::uuid uuid);

    private:
        ReadMessage & m_readMessage;
        WriteMessage m_writeMessage;
        const std::string & m_mail;
        const std::string & m_ip;
        const short & m_port;
        ChatRoom & m_chat_room;
        boost::uuids::uuid & m_uuid;
};

#endif /* !CALL_HPP_ */
