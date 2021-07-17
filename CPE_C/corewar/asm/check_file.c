/*
** EPITECH PROJECT, 2019
** check_file
** File description:
** check if it's a good file
*/

#include "my.h"

int check_this_param(asm_t *com, int i, int j, op_t op)
{
    if (j == 0) {
        if (com->param[i][j] == DIRECT_CHAR && op.type[i] & T_DIR)
            return (0);
        if (com->param[i][j] == 'r' && op.type[i] & T_REG)
            return (0);
        if (com->param[i][j] == LABEL_CHAR && op.type[i] & T_IND && labcheck\
(com->param[i], com))
            return (16);
        if (com->param[i][j] != DIRECT_CHAR && com->param[i][j] != LABEL_CHAR \
&& com->param[i][j] != 'r' && op.type[i] & T_IND)
            return (0);
        my_dprintf(2, "Invalid type of parameters or invalid label for %s: \
%s\n", com->arg, com->param[i]);
        return (84);
    }
    if ((com->param[i][j] >= '0' && com->param[i][j] <= '9') || com->param[i]\
[j] == '-')
        return (0);
    return invalid_label_parameters(com, i, j);
}

static int check_params(asm_t *com, op_t op)
{
    int check = 0;

    for (int i = 0; com->param[i] != NULL; i++) {
        check = condition_checks_params(i, check, com, op);
        if (check == -100)
            return (84);
    }
    return (1);
}

int check_struct(asm_t *commands, op_t *opstruct, int i)
{
    int nb = 0;

    for (; commands->param[nb] != NULL; nb++);
    if (nb != opstruct[i].nbr_args) {
        my_dprintf(2, "Invalid number of parameters for %s: got %d but \
expected %d\n", commands->arg, nb, opstruct[i].nbr_args);
        return (84);
    }
    if (check_params(commands, opstruct[i]) == 84)
        return (84);
    return (1);
}

static int check_label(asm_t *list)
{
    asm_t *mem = NULL;

    for (; list != NULL; list = list->next) {
        mem = list->next;
        if (condition_check_label(list, mem) == 0)
            return (0);
    }
    return (1);
}

int check_file(asm_t *commands)
{
    op_t *opstruct = op_tab;

    if (!check_header(commands))
        return (84);
    if (!check_label(commands))
        return (84);
    for (int check = 0; commands != NULL; commands = commands->next) {
        check = condition_check_file(commands, check, opstruct);
        if (check == -100)
            return (84);
        check = 0;
    }
    return (1);
}
