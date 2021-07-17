/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** call_struct
*/

#ifndef CALL_STRUCT_H_
#define CALL_STRUCT_H_

#include "structurebase.h"

typedef struct call_s {
    header_t header;
    char mail[LOGIN_LENGTH];
}call_t;

typedef struct call_answer_s {
    header_t header;
    char ip[IP_LENGTH];
    short port;
}call_answer_t;

typedef struct got_call_s{
    header_t header;
    char mail[LOGIN_LENGTH];
    char ip [IP_LENGTH];
    short port;
}got_call_t;

typedef struct left_call_s {
    header_t header;
    char ip[IP_LENGTH];
}left_call_t;

#endif /* !CALL_STRUCT_H_ */
