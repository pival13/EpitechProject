/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** status_struct
*/

#ifndef STATUS_STRUCT_H_
#define STATUS_STRUCT_H_

#include "structurebase.h"

typedef struct new_status_s {
  header_t header;
  status_t status;
}new_status_t;

typedef struct status_changed_s {
    header_t header;
    char mail[LOGIN_LENGTH];
    status_s status;
}status_changed_t;


#endif /* !STATUS_STRUCT_H_ */
