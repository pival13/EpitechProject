/*
** EPITECH PROJECT, 2018
** get_next_line.h
** File description:
** for macros and prototypes
*/

#ifndef READ_SIZE
#define READ_SIZE (8)
#endif

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

typedef struct gnl_vars {
    char *cnt;
    int nbline;
    int nbline_max;
    int fd_moment;
} gnl;

char *get_next_line(int fd);

#endif
