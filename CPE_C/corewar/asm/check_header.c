/*
** EPITECH PROJECT, 2019
** check header
** File description:
** check header
*/

#include "my.h"

static char *get_str(char *file, int size)
{
    char *str = malloc(size);
    int mem = 0;

    if (str == NULL)
        return (NULL);
    for (int i = 0; i != size; i++)
        str[i] = 0;
    for (int i = 0; file[i] != '\0'; i++)
        if (file[i] == '\"') {
            mem = i+1;
            break;
        }
    for (int j = 0; j != size; j++)
        if (file[mem+j] == '\"' || file[mem+j] == '\0')
            break;
        else
            str[j] = file[mem+j];
    free(file);
    return (str);
}

int verify_len_name(asm_t *save, int len)
{
    int j = 0;
    int i = 0;

    for (; save->arg[i] != '\"' && save->arg[i] != '\0'; i++);
    i++;
    for (; save->arg[i] != '\"' && save->arg[i] != '\0'; i++, j++);
    if (j > len)
        return 0;
    return 1;
}

int print_probleme(void)
{
    my_dprintf(2, "Bad name's or comment's length\n");
    return 0;
}

int error_name_comment(int name, int comment)
{
    if (name != 1 && comment != 1)
        my_dprintf(2, "Invalid name and comment\n");
    else if (name != 1)
        my_dprintf(2, "Invalid name\n");
    else
        my_dprintf(2, "Invalid comment\n");
    return 0;
}

int check_header(asm_t *list)
{
    int name = 0;
    int comment = 0;
    asm_t *save = list;

    for (; save != NULL; save = save->next)
        if (save->other == 1)
            name++;
        else if (save->other == 2)
            comment++;
    if (name != 1 || comment != 1)
        return error_name_comment(name, comment);
    if (verify_cote(list, 1, NAME_CMD_STRING, PROG_NAME_LENGTH) == 0 || verify_\
cote(list, 2, COMMENT_CMD_STRING, COMMENT_LENGTH) == 0)
        return 0;
    for (; list != NULL; list = list->next)
        if (list->other == 1)
            list->arg = get_str(list->arg, PROG_NAME_LENGTH);
        else if (list->other == 2)
            list->arg = get_str(list->arg, COMMENT_LENGTH);
    return 1;
}
