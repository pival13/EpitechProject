/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** message_struct
*/

#ifndef MESSAGE_STRUCT_H_
#define MESSAGE_STRUCT_H_

#include "structurebase.h"

typedef struct message_s {
    header_t header;
    char mail[LOGIN_LENGTH];
    char message[MESSAGE_LENGTH];
    size_t timestamp;
}message_t;

#endif /* !MESSAGE_STRUCT_H_ */
