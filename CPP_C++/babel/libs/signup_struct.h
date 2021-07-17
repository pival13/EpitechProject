/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** signup_struct
*/

#ifndef SIGNUP_STRUCT_H_
#define SIGNUP_STRUCT_H_

#include "structurebase.h"

typedef struct signup_s {
   header_t header;
   char mail[LOGIN_LENGTH];
   char password[LOGIN_LENGTH];
   char username[LOGIN_LENGTH];
   short port;
}signup_t;

#endif /* !SIGNUP_STRUCT_H_ */
