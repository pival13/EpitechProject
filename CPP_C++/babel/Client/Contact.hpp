/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** Contact
*/

#pragma once

#include "TCPConnection.hpp"
#include "Message.hpp"

class Contact {
    public:
        Contact(std::string email, std::string name, status_t status) {mail = email;username = name;stat = status;};
        ~Contact() = default;
        
        const std::string &getMail() const {return mail;};
        const std::string &getUsername() const {return username;};
        const status_t getStatus() const {return stat;};

        std::list<Message> & getPendingMessage() {return pendingList;};
        std::list<Message> & getMessageList() {return messageList;};
        const std::list<Message> & getMessageList() const {return messageList;};

        void setStatus(status_t status) {stat = status;};
    protected:
    private:
        std::string mail;
        std::string username;
        status_t stat;

        std::list<Message> pendingList;
        std::list<Message> messageList;
};
