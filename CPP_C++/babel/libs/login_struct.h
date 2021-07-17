/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** login_struct
*/

#ifndef LOGIN_STRUCT_H_
#define LOGIN_STRUCT_H_

#include "structurebase.h"

typedef struct login_s {
    header_t header;
    char mail[LOGIN_LENGTH];
    char password[LOGIN_LENGTH];
    short port;
}login_t;

#endif /* !LOGIN_STRUCT_H_ */
