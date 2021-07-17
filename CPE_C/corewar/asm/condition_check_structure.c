/*
** EPITECH PROJECT, 2019
** check_file
** File description:
** check if it's a good file
*/

#include "my.h"

int condition_check_file(asm_t *commands, int check, op_t *opstruct)
{
    if (commands->other == 0) {
        check = check_mnemonique(check, commands, opstruct);
        if (!check && commands->arg && commands->arg[0])
            my_dprintf(2, "Unknow function\n");
        if ((!check && commands->arg && commands->arg[0]) || check == 84) {
            check = -100;
            return (check);
        }
        commands->size = find_size_asm(commands);
    }
    return (check);
}

int condition_checks_params(int i, int check, asm_t *com, op_t op)
{
    for (int j = 0; com->param[i][j] != '\0'; j++) {
        check = check_this_param(com, i, j, op);
        if (check == 84) {
            check = -100;
            return (check);
        }
        else if (check == 16)
            j = my_strlen(com->param[i])-1;
    }
    return (check);
}

int condition_check_label(asm_t *list, asm_t *mem)
{
    for (; list->label && mem != NULL; mem = mem->next) {
        if (!my_strcmp(list->label, mem->label)) {
            my_dprintf(2, "Double label: %s\n", list->label);
            return (0);
        }
    }
    return (1);
}
