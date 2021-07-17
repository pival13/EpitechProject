/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** AddFriend
*/

#include "AddFriend.hpp"

AddFriend::AddFriend(ReadMessage& ReadMessage, WriteMessage &writeMessage,
        const std::string& mail, const std::string & dbPath)
    : m_readMessage(ReadMessage),
    m_writeMessage(writeMessage),
    m_mail(mail),
    m_dbPath(dbPath)
{
}

AddFriend::~AddFriend()
{
}

/**
 * @brief Check if users exist inside the database.
 * 
 * @param mail Mail address of the client to check.
 * @return true If the client is present inside the databse.
 * @return false If the client isn't present inside it.
 */
bool AddFriend::checkUser(const std::string & mail)
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
void AddFriend::AddFriendFailed()
{
    header_t header;

    header.size = 0;
    header.func = ADD_FRIEND_ERROR;
    this->m_writeMessage.setData(&header, sizeof(header_t));
}

/**
 * @brief Send Failed at the client.
 * 
 * @param friendMail Client's mail address which can not be add inside the db
 */
void AddFriend::AddFriendFailed(const std::string & friendMail)
{
    mail_t mail;

    mail.header.size = sizeof(mail_t) - sizeof(header_t);
    mail.header.func = ADD_FRIEND_ERROR;
    std::memset(mail.mail, 0, LOGIN_LENGTH);
    std::memcpy(mail.mail, friendMail.data(), friendMail.size());
    this->m_writeMessage.setData(&mail, sizeof(mail_t));
}

/**
 * @brief Get your ID.
 * 
 * @return int Your ID.
 */
int AddFriend::getUserId()
{
    MySqlite sql(this->m_dbPath);
    std::string request = "select _rowid_ from users where mail='"
            + this->m_mail + "';";
    sqltable result;

    result = sql.excuteSelect(request);
    return std::stoi(result.at("rowid").at(0));
}

/**
 * @brief Get username, mail, and status about the new Friend.
 * 
 * @param mail Mail adress of the new friend.
 * @return sqltable Informations about the new Friend.
 */
sqltable AddFriend::getInformationAboutContact(const std::string &mail)
{
    sqltable result;
    MySqlite sql(this->m_dbPath);
    std::string request = "select username, mail, status from users where mail='"
            + mail + "';";

    return sql.excuteSelect(request);
}

/**
 * @brief Add the new contact inside the database, and set the answer.
 * 
 * @param mail Mail Adress at the Friend to add/
 */
void AddFriend::AddFriendSuccess(const std::string & mail)
{
    int id = getUserId();
    MySqlite sql(this->m_dbPath);
    get_contact_t contact;
    sqltable result;
    std::string request = "insert into contacts ('email','UserId') values('"
            + mail + "','" + std::to_string(id) + "');";

    if (sql.excuteInsert(request) == false) {
        std::cerr << request << std::endl;
        throw std::runtime_error("Add Friend request has failed");
    } else {
        result = getInformationAboutContact(mail);
        contact.header.size = sizeof(get_contact_t) - sizeof(header_t);
        contact.header.func = GET_CONTACT;
        if (!result.empty()) {
            std::memset(contact.mail, 0, LOGIN_LENGTH);
            std::memcpy(contact.mail, result.at("mail").at(0).data(), result.at("mail").at(0).size());
            std::memset(contact.username, 0, LOGIN_LENGTH);
            std::memcpy(contact.username, result.at("username").at(0).data(), result.at("username").at(0).size());
            contact.status = (status_t)std::stoi(result.at("status").at(0));
            this->m_writeMessage.setData(&contact, sizeof(get_contact_t));
        }
        std::memset(contact.mail, 0, LOGIN_LENGTH);
        std::memset(contact.username, 0, LOGIN_LENGTH);
        contact.status = OFFLINE;
        if (result.empty()) {
            this->m_writeMessage.setData(&contact, sizeof(get_contact_t));
        } else {
            this->m_writeMessage.addData(&contact, sizeof(get_contact_t));
        }
    }
}

/**
 * @brief Create the answer of the AddFriend client request.
 * 
 */
void AddFriend::getAnswer()
{
    add_friend_t addFriend = this->m_readMessage.getAddFriend();

    if (addFriend.mail == NULL || this->m_mail.empty() ||
        std::strcmp(addFriend.mail, this->m_mail.data()) == 0) {
        AddFriendFailed();
        return;
    }
    if (checkUser(std::string(addFriend.mail)) == false)
        AddFriendFailed(addFriend.mail);
    else {
        try {
            AddFriendSuccess(std::string(addFriend.mail));
        } catch (std::exception & err) {
            std::cout << err.what() << std::endl;
        }
    }
}
