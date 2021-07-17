/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** ReadMessage
*/

#ifndef READMESSAGE_HPP_
#define READMESSAGE_HPP_

#include <iostream>
#include <cstring>
#include <vector>
#include "../libs/lib_client_server.h"

class ReadMessage
{
    public:
        ReadMessage();
        ReadMessage(std::string);
        ~ReadMessage();
        void addCommand(std::vector<char>);
        const std::size_t getDataLength();
        const header_t getHeader();
        const login_t getLogin();
        const signup_t getSignUp();
        const add_friend_t getAddFriend();
        const delete_friend_t getDeleteFriend();
        const get_contact_message_t getContactMessage();
        const get_contact_t getContact();
        const new_status_t getNewStatus();
        const call_t getCall();
        const left_call_t getLeftCall();
        const message_t getMessage();
        const mail_t getMail();
        const std::size_t getLength() const;
        const std::vector<char> getData() const;
        void setData(std::vector<char>);
        void setLength(std::size_t);
        void deletePartOfData(std::size_t);

    private:
        std::vector<char> data;
        std::size_t length;
};

#endif /* !READMESSAGE_HPP_ */
