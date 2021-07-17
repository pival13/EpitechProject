/*
** EPITECH PROJECT, 2020
** Created by theo on 09/06/2020.
** File description:
** remove_node.c
*/

#include "my.h"

teams_t *remove_teams_second(teams_t *mem)
{
    teams_t *tmp = mem->next;
    my_free(mem->name);
    my_free(mem);

    return tmp;
}

teams_t *remove_teams(teams_t *teams, int nbr)
{
    teams_t *mem = teams;

    if (mem == NULL) return NULL;
    if (mem->nbr == nbr) return remove_teams_second(mem);
    for (teams_t *tmp; mem->next != NULL; mem = mem->next) {
        if (mem->next->nbr == nbr) {
            if (mem->next->next == NULL) {
                my_free(mem->next->name);
                my_free(mem->next);
                mem->next = NULL;
            } else {
                tmp = mem->next;
                mem->next = tmp->next;
                my_free(tmp->name);
                my_free(tmp);
            }
            break;
        }
    }
    return teams;
}

com_pile_t *remove_command(com_pile_t *pile)
{
    com_pile_t *tmp = pile;

    pile = pile->next;
    my_free(tmp->command);
    my_free(tmp);
    return pile;
}