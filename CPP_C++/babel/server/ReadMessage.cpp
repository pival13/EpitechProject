/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** ReadMessage
*/

#include "ReadMessage.hpp"

ReadMessage::ReadMessage()
{
}

ReadMessage::ReadMessage(std::string buffer)
    : data(buffer.data(), buffer.data() + buffer.size())
{
}

ReadMessage::~ReadMessage()
{
}

/**
 * @brief add Command to the currently data.
 *
 * @param buffer Command to add.
 */
void ReadMessage::addCommand(std::vector<char> buffer)
{
    this->data.insert(this->data.end(), buffer.begin(), buffer.end());
}

/**
 * @brief Return the size of the data.
 *
 * @return const std::size_t Size of the data.
 */
const std::size_t ReadMessage::getDataLength()
{
    return this->data.size();
}

/**
 * @brief Get a header inside the data.
 *
 * @return const header_t The first header found inside the data.
 */
const header_t ReadMessage::getHeader()
{
    header_t header;

    std::memcpy((char *)&header, this->data.data(), sizeof(header_t));
    if (header.size == 0)
        deletePartOfData(sizeof(header_t) + 3);
    else
        deletePartOfData(sizeof(header_t));
    return header;
}

/**
 * @brief Get a login Information.
 *
 * @return const login_t All login's informations.
 */
const login_t ReadMessage::getLogin()
{
    login_t login;

    std::memcpy((char *)&login + sizeof(header_t),
            this->data.data(), sizeof(login_t) - sizeof(header_t));

    deletePartOfData(sizeof(login) - sizeof(header_t) + 3);
    return login;
}

/**
 * @brief get a signup information.
 *
 * @return const signup_t sign up's information.
 */
const signup_t ReadMessage::getSignUp()
{
    signup_t signUp;

    std::memcpy((char*)&signUp + sizeof(header_t),
            this->data.data(), sizeof(signup_t) - sizeof(header_t));
    deletePartOfData(sizeof(signup_t) - sizeof(header_t) + 3);
    return signUp;
}

/**
 * @brief get information about the add friend request.
 *
 * @return const add_friend_t All informations about request.
 */
const add_friend_t ReadMessage::getAddFriend()
{
    add_friend_t addFriend;

    std::memcpy((char*)&addFriend + sizeof(header_t),
            this->data.data(), sizeof(add_friend_t) - sizeof(header_t));
    deletePartOfData(sizeof(add_friend_t) - sizeof(header_t) + 3);
    return addFriend;
}

/**
 * @brief get information about the delete friend request.
 *
 * @return const add_friend_t All informations about request.
 */
const delete_friend_t ReadMessage::getDeleteFriend()
{
    delete_friend_t deleteFriend;

    std::memcpy((char*)&deleteFriend + sizeof(header_t),
            this->data.data(), sizeof(delete_friend_t) - sizeof(header_t));
    deletePartOfData(sizeof(delete_friend_t) - sizeof(header_t) + 3);
    return deleteFriend;
}

/**
 * @brief get information about the get contact message request.
 *
 * @return const add_friend_t All informations about request.
 */
const get_contact_message_t ReadMessage::getContactMessage()
{
    get_contact_message_t getContactMessage;

    std::memcpy((char*)&getContactMessage + sizeof(header_t),
            this->data.data(), sizeof(get_contact_message_t) - sizeof(header_t));
    deletePartOfData(sizeof(get_contact_message_t) - sizeof(header_t) + 3);
    return getContactMessage;
}

/**
 * @brief get information about the new status request.
 *
 * @return const add_friend_t All informations about request.
 */
const new_status_t ReadMessage::getNewStatus()
{
    new_status_t newStatus;

    std::memcpy((char*)&newStatus + sizeof(header_t),
            this->data.data(), sizeof(new_status_t) - sizeof(header_t));
    deletePartOfData(sizeof(new_status_t) - sizeof(header_t) + 3);
    return newStatus;
}

/**
 * @brief get information about the call request.
 *
 * @return const add_friend_t All informations about request.
 */
const call_t ReadMessage::getCall()
{
    call_t Call;

    std::memcpy((char*)&Call + sizeof(header_t),
            this->data.data(), sizeof(call_t) - sizeof(header_t));
    deletePartOfData(sizeof(call_t) - sizeof(header_t) + 3);
    return Call;
}

/**
 * @brief Get Mail
 * 
 * @return const mail_t mail
 */
const mail_t ReadMessage::getMail()
{
    mail_t mail;

    std::memcpy((char*)&mail + sizeof(header_t),
            this->data.data(), sizeof(mail_t) - sizeof(header_t));
    deletePartOfData(sizeof(mail_t) - sizeof(header_t) + 3);
    return mail;
}

/**
 * @brief get information about the message request.
 *
 * @return const add_friend_t All informations about request.
 */
const message_t ReadMessage::getMessage()
{
    message_t message;

    std::memcpy((char*)&message + sizeof(header_t),
            this->data.data(), sizeof(message_t) - sizeof(header_t));
    deletePartOfData(sizeof(message_t) - sizeof(header_t) + 3);
    return message;
}

/**
 * @brief Get informations about the left call request.
 * 
 * @return const left_call_t All information about the request.
 */
const left_call_t ReadMessage::getLeftCall()
{
    left_call_t leftCall;

    std::memcpy((char*)&leftCall + sizeof(header_t),
            this->data.data(), sizeof(left_call_t) - sizeof(header_t));
    deletePartOfData(sizeof(left_call_t) - sizeof(header_t) + 3);
    return leftCall;
}

/**
 * @brief Delete n bytes of the data.
 *
 * @param length n bytes which are going to be deleted.
 */
void ReadMessage::deletePartOfData(std::size_t length)
{
    this->data.erase(this->data.begin(), this->data.begin() + length);
}

/**
 * @brief Return data's length.
 *
 * @return const std::size_t data's length.
 */
const std::size_t ReadMessage::getLength() const
{
    return this->length;
}

/**
 * @brief set new length.
 *
 * @param length new length.
 */
void ReadMessage::setLength(std::size_t length)
{
    this->length = length;
}

/**
 * @brief Return data.
 *
 * @return const std::string data.
 */
const std::vector<char> ReadMessage::getData() const
{
    return this->data;
}

/**
 * @brief set contain of new data.
 *
 * @param data Contain of new data.
 */
void ReadMessage::setData(std::vector<char> data)
{
    addCommand(data);
}
