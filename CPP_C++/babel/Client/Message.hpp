/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** Message
*/

#pragma once

#include <string>

class Message {
    public:
        Message(const std::string & sender_mail, const std::string & receiver_mail, const std::string & messages, int times) {sender = sender_mail; receiver = receiver_mail; message = messages, time = times;};
        ~Message() = default;

        //get
        std::string getSender() {return sender;};
        const std::string &getSender() const {return sender;};
        std::string getMessage() {return message;};
        const std::string &getMessage() const {return message;};
        std::string getReceiver() {return receiver;};
        const std::string &getReceiver() const {return receiver;};
        int getTime() const {return time;};

    private:
        std::string sender; 
        std::string receiver;
        std::string message;

        unsigned long time;
};
