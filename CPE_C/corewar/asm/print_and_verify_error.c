/*
** EPITECH PROJECT, 2019
** print
** File description:
** display and verify
*/

#include "my.h"

int invalid_label_parameters(asm_t *com, int i, int j)
{
    if (com->param[i][j] == LABEL_CHAR && labcheck(com->param[i], com))
        return (16);
    my_dprintf(2, "Invalid type of parameters or invalid label %s: %s\n", \
com->arg, com->param[i]);
    return (84);
}

int verify_string(asm_t *save, char *string, int lenght)
{
    int len = 0;

    for (len = 0; save->arg[len+1] != '\"' && save->arg[len] != '\0'; len++)
        if (save->arg[len] != string[len]) {
            my_dprintf(2, "Misplaced cote on name or comment\n");
            return 0;
        }
    if (save->arg[len+1] != '\"') {
        my_dprintf(2, "Misplaced cote on name or comment\n");
        return 0;
    }
    for (len = my_strlen(save->arg)-1; len >= 0 && \
save->arg[len] == ' '; len--);
    if (save->arg[len] != '\"') {
        my_dprintf(2, "Misplaced cote on name or comment\n");
        return 0;
    }
    if (verify_len_name(save, lenght) == 0)
        return print_probleme();
    return 1;
}

int verify_cote(asm_t *list, int a, char *string, int len)
{
    asm_t *save = list;
    int verify = 0;

    for (; save->next != NULL; save = save->next)
        if (save->other == a)
            break;
    for (int i = 0; save->arg[i] != '\0'; i++)
        if (save->arg[i] == '\"')
            verify++;
    if (verify != 2) {
        my_dprintf(2, "Not enough cote between name or comment\n");
        return 0;
    }
    if (verify_string(save, string, len) == 0)
        return 0;
    return 1;
}
