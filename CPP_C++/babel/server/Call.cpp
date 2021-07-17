/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** Call
*/

#include "Call.hpp"

Call::Call(ReadMessage & readMessage, const std::string & ip,
        const short & port, ChatRoom & chatRoom, const std::string & mail,
        boost::uuids::uuid & uuid)
    : m_readMessage(readMessage),
    m_ip(ip),
    m_port(port),
    m_chat_room(chatRoom),
    m_mail(mail),
    m_uuid(uuid)
{
}

Call::~Call()
{
}

/**
 * @brief Send call request to another user.
 * 
 */
void Call::sendRequest()
{
    call_t call = this->m_readMessage.getCall();
    boost::shared_ptr<Participant> tmp;
    got_call_t gotCall;

    gotCall.header.func = GOT_CALL;
    gotCall.header.size = sizeof(got_call_t) - sizeof(header_t);
    gotCall.port = this->m_port;
    std::memset(gotCall.ip, 0, IP_LENGTH);
    std::memcpy(gotCall.ip, this->m_ip.data(), this->m_ip.size());
    std::memset(gotCall.mail, 0, LOGIN_LENGTH);
    std::memcpy(gotCall.mail, this->m_mail.data(), this->m_mail.size());
    this->m_writeMessage.setData(&gotCall, sizeof(got_call_t));
    tmp = this->m_chat_room.getParticipant(std::string(call.mail));
    if (tmp != nullptr)
        tmp->WriteStatusBuffer(this->m_writeMessage);
}

/**
 * @brief Send the client's answer (Accept/Refuse Call)
 * and create the call room.
 * @param type Accept or Refuse Call
 */
void Call::sendAnswer(type_t type)
{
    mail_t mail = this->m_readMessage.getMail();
    call_answer_t callAnswer;
    header_t header;
    boost::shared_ptr<Participant> myself;
    boost::shared_ptr<Participant> stranger;

    header.size = 0;
    header.func = type;
    this->m_writeMessage.setData(&header, sizeof(header_t));
    myself = this->m_chat_room.getParticipant(this->m_mail);
    if (myself == nullptr)
        throw std::runtime_error("Can't find " + this->m_mail + " user");
    this->m_writeMessage.setData(&header, sizeof(header_t));
    stranger = this->m_chat_room.getParticipant(mail.mail);
    if (stranger == nullptr)
        throw std::runtime_error("Can't find " + std::string(mail.mail) + " user");
    stranger->WriteStatusBuffer(this->m_writeMessage);
    if (type == ACCEPT_CALL) {
        if (!this->m_chat_room.getParticipant(mail.mail)->getUUid().is_nil()) {
            addParticipant(this->m_chat_room.getParticipant(mail.mail)->getUUid());
            return;
        }
        this->m_uuid = this->m_chat_room.createCall(myself, stranger);
        callAnswer.port = this->m_port;
        callAnswer.header.func = JOIN_CALL;
        callAnswer.header.size = sizeof(call_answer_t) - sizeof(header_t);
        callAnswer.port = this->m_port;
        std::memset(callAnswer.ip, 0, IP_LENGTH);
        std::memcpy(callAnswer.ip, this->m_ip.data(), this->m_ip.size());
        stranger->setUuid(this->m_uuid);
        this->m_writeMessage.setData(&callAnswer, sizeof(call_answer_t));
        stranger->WriteStatusBuffer(this->m_writeMessage);
        std::memset(callAnswer.ip, 0, IP_LENGTH);
        std::memcpy(callAnswer.ip, stranger->getIp().data(), stranger->getIp().size());
        callAnswer.port = stranger->getPort();
        this->m_writeMessage.setData(&callAnswer, sizeof(call_answer_t));
        myself->WriteStatusBuffer(this->m_writeMessage);
    }
}

/**
 * @brief Add participant to an call.
 * 
 * @param uuid Uuid of the call.
 */
void Call::addParticipant(boost::uuids::uuid uuid)
{
    this->m_uuid = uuid;
    boost::shared_ptr<Participant> myself = this->m_chat_room.getParticipant(this->m_mail);
    auto & listCall = this->m_chat_room.getParticipantCall(uuid);
    call_answer_t callAnswer;

    this->m_chat_room.addUserToACall(uuid, myself);
    if (!listCall.empty()) {
        callAnswer.header.size = sizeof(call_answer_t) - sizeof(header_t);
        callAnswer.header.func = JOIN_CALL;
        callAnswer.port = this->m_port;
        std::memset(callAnswer.ip, 0, IP_LENGTH);
        std::memcpy(callAnswer.ip, this->m_ip.data(), this->m_ip.size());
        this->m_writeMessage.setData(&callAnswer, sizeof(call_answer_t));
        for (auto it = listCall.begin(); it != listCall.end(); ++it) {
            (*it)->WriteStatusBuffer(this->m_writeMessage);
        }
        for (auto it = listCall.begin(); it != listCall.end(); ++it) {
            std::memset(callAnswer.ip, 0, IP_LENGTH);
            std::memcpy(callAnswer.ip, (*it)->getIp().data(), (*it)->getIp().size());
            callAnswer.port = (*it)->getPort();
            if (it == listCall.begin()) {
                this->m_writeMessage.setData(&callAnswer, sizeof(call_answer_t));
            } else {
                this->m_writeMessage.addData(&callAnswer, sizeof(call_answer_t));
            }
        }
        myself->WriteStatusBuffer(this->m_writeMessage);
    }
}

/**
 * @brief Left a Call.
 * 
 */
void Call::leftCall()
{
    WriteMessage message;
    left_call_t answer;

    answer.header.func = LEFT_CALL;
    answer.header.size = sizeof(left_call_t) - sizeof(header_t);
    std::memset(answer.ip, 0, IP_LENGTH);
    std::memcpy(answer.ip, this->m_ip.data(), this->m_ip.size());

    auto &listCall = this->m_chat_room.getParticipantCall(this->m_uuid);
    this->m_chat_room.deleteUserToACall(this->m_uuid, this->m_chat_room.getParticipant(this->m_mail));
    if (!listCall.empty()) {
        message.setData(&answer, sizeof(left_call_t));
        for (auto it = listCall.begin(); it != listCall.end(); ++it)
            (*it)->WriteStatusBuffer(message);
    }
    this->m_uuid = {00000000-0000-0000-0000-000000000000};
}
