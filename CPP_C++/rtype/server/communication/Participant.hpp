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
#include <boost/enable_shared_from_this.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

class Participant {
    public:
        virtual ~Participant() {};
        virtual const boost::uuids::uuid getUuid() const = 0;
        virtual const std::string getName() const = 0;
};

#endif /* !PARTICIPANT_HPP_ */
