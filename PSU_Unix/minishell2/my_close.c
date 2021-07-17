/*
** EPITECH PROJECT, 2019
** m_close
** File description:
** close and reset to -1
*/

#include "minishell.h"

void my_close(int *fd)
{
    if (*fd != -1)
        close(*fd);
    *fd = -1;
}