/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** get_contact_struct
*/

#ifndef GET_CONTACT_STRUCT_H_
#define GET_CONTACT_STRUCT_H_

#include "structurebase.h"

typedef struct get_contact_s {
    header_t header;
    char mail[LOGIN_LENGTH];
    char username[LOGIN_LENGTH];
    status_t status;
}get_contact_t;

#endif /* !GET_CONTACT_STRUCT_H_ */
