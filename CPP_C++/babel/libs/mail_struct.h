/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** mail_struct
*/

#ifndef MAIL_STRUCT_H_
#define MAIL_STRUCT_H_

#include "structurebase.h"

typedef struct mail_s {
    header_t header;
    char mail[LOGIN_LENGTH];
}mail_t;

#endif /* !MAIL_STRUCT_H_ */
