/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** structurebase
*/

#ifndef STRUCTUREBASE_H_
#define STRUCTUREBASE_H_

#define MESSAGE_LENGTH 160
#define LOGIN_LENGTH 64
#define IP_LENGTH 16

typedef enum type_s {
    LOGIN,
    LOGIN_ERROR,
    ADD_FRIEND,
    ADD_FRIEND_ERROR,
    DELETE_FRIEND,
    DELETE_FRIEND_ERROR,
    DELETE_FRIEND_SUCCESS,
    GET_CONTACT_MESSAGE,
    GET_CONTACT_MESSAGE_FAILED,
    GET_CONTACT_MESSAGE_ANSWER,
    GET_CONTACT,
    NEW_STATUS,
    STATUS_CHANGED,
    MESSAGE,
    MESSAGE_SUCCESS,
    MESSAGE_FAILED,
    DISCONNECT,
    SIGN_UP,
    SIGN_UP_ERROR,
    CALL,
    GOT_CALL,
    REFUSE_CALL,
    ACCEPT_CALL,
    END_CALL,
    START_CALL,
    LEFT_CALL,
    JOIN_CALL
}type_t;

typedef enum status_s {
    ONLINE,
    NODISTURB,
    OFFLINE,
}status_t;

typedef struct header_s {
    type_t func;
    unsigned short size;
}header_t;

#endif /* !STRUCTUREBASE_H_ */
