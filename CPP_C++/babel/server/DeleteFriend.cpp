/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** DeleteFriend
*/

#include "DeleteFriend.hpp"

DeleteFriend::DeleteFriend(ReadMessage& readMessage,
        WriteMessage& writeMessage, const std::string & mail,
        const std::string & dbPath)
    : m_readMessage(readMessage),
    m_writeMessage(writeMessage),
    m_mail(mail),
    m_dbPath(dbPath)
{
}

DeleteFriend::~DeleteFriend()
{
}

/**
 * @brief Check if users exist inside the database.
 * 
 * @param mail Mail address of the client to check.
 * @return true If the client is present inside the databse.
 * @return false If the client isn't present inside it.
 */
bool DeleteFriend::checkUser(const std::string & mail)
{
    MySqlite sql(this->m_dbPath);
    std::string selectRequest = "select username from users where mail='"
            + mail + "';";
    sqltable result;

    result = sql.excuteSelect(selectRequest);
    if (result.empty())
        return false;
    return true;
}

/**
 * @brief Send Failed at the client, when we don't have the client's mail adress.
 * 
 */
void DeleteFriend::deleteFriendFailed()
{
    header_t header;

    header.size = 0;
    header.func = DELETE_FRIEND_ERROR;
    this->m_writeMessage.setData(&header, sizeof(header_t));
}

/**
 * @brief Send Failed at the client.
 * 
 * @param friendMail Client's mail address which can not be add inside the db
 */
void DeleteFriend::deleteFriendFailed(const std::string & friendMail)
{
    mail_t mail;

    mail.header.size = sizeof(mail_t) - sizeof(header_t);
    mail.header.func = DELETE_FRIEND_ERROR;
    std::memset(mail.mail, 0, LOGIN_LENGTH);
    std::memcpy(mail.mail, friendMail.data(), friendMail.size());
    this->m_writeMessage.setData(&mail, sizeof(mail_t));
}

/**
 * @brief Get the ID of the current client.
 * 
 * @return int The ID of the current client.
 */
int DeleteFriend::getUserId()
{
    MySqlite sql(this->m_dbPath);
    std::string request = "select _rowid_ from users where mail='"
            + this->m_mail + "';";
    sqltable result;

    result = sql.excuteSelect(request);
    return std::stoi(result.at("rowid").at(0));
}

/**
 * @brief Set Success DeleteFriend request.
 * 
 * @param friendMail Client's mail address which has been added at the db.
 */
void DeleteFriend::deleteFriendSuccess(const std::string & friendMail)
{
    int id = getUserId();
    MySqlite sql(this->m_dbPath);
    get_contact_t contact;
    sqltable result;
    mail_t mail;
    std::string request = "delete from contacts where email='"
            + friendMail + "' AND UserId=" + std::to_string(id) + ";";

    if (sql.excuteInsert(request) == false) {
        std::cerr << request << std::endl;
        deleteFriendFailed(friendMail);
        throw std::runtime_error("Add Friend request has failed");
    } else {
        mail.header.size = sizeof(mail_t) - sizeof(header_t);
        mail.header.func = DELETE_FRIEND_SUCCESS;
        std::memset(mail.mail, 0, LOGIN_LENGTH);
        std::memcpy(mail.mail, friendMail.data(), friendMail.size());
        this->m_writeMessage.setData(&mail, sizeof(mail_t));
    }
}

/**
 * @brief Make the answer of the client's DeleteFriend request
 * 
 */
void DeleteFriend::getAnswer()
{
    delete_friend_t deleteFriend = this->m_readMessage.getDeleteFriend();

    if (deleteFriend.mail == NULL || this->m_mail.empty()
            || this->m_mail.empty()) {
        deleteFriendFailed();
        return;
    }
    if (checkUser(std::string(deleteFriend.mail)) == false)
        deleteFriendFailed(std::string(deleteFriend.mail));
    else {
        try {
            deleteFriendSuccess(std::string(deleteFriend.mail));
        } catch (const std::exception & err) {
            std::cerr << err.what() << std::endl;
            deleteFriendFailed();
        }
    }
}
