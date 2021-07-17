/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** Participant
*/

#ifndef PARTICIPANT_HPP_
#define PARTICIPANT_HPP_

#include <set>
#include <iostream>
#include <boost/uuid/uuid.hpp>

#include "WriteMessage.hpp"

class Participant {
    public:
        virtual ~Participant() {};
        virtual std::string getParticipantMail() = 0;
        virtual void WriteStatusBuffer(WriteMessage writeMessage) = 0;
        virtual short getPort() = 0;
        virtual std::string getIp() = 0;
        virtual void setUuid(boost::uuids::uuid uuid) = 0;
        virtual boost::uuids::uuid getUUid() const = 0;
};

#endif /* !PARTICIPANT_HPP_ */
