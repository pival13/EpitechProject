/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** get_contact_message
*/

#ifndef GET_CONTACT_MESSAGE_H_
#define GET_CONTACT_MESSAGE_H_

#include "structurebase.h"

typedef struct get_contact_message_s {
    header_t header;
    char mail[LOGIN_LENGTH];
    size_t number;
}get_contact_message_t;

typedef struct get_contact_message_answer_s {
    header_t header;
    char receiver[LOGIN_LENGTH];
    char sender[LOGIN_LENGTH];
    char message[MESSAGE_LENGTH];
    size_t timestamp;
}get_contact_message_answer_t;

#endif /* !GET_CONTACT_MESSAGE_H_ */
