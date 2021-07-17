/*
** EPITECH PROJECT, 2019
** check_label.c
** File description:
** Created by etienne-miltgen,
*/

#include "my.h"

static int check_labchar(char c)
{
    char *chars = LABEL_CHARS;
    for (int i = 0; chars[i] != '\0'; i++) {
        if (chars[i] == c)
            return (1);
    }
    return (84);
}

static char *create_labstr(char *str, int i)
{
    int j = 0;
    char *lab = NULL;
    char c = LABEL_CHAR;

    if (str[i] == c)
        i++;
    lab = malloc(sizeof(char) * (my_lablen(str, i) + 1));
    if (lab == NULL)
        return (NULL);
    while (str[i] != '\0') {
        lab[j] = str[i];
        j++;
        i++;
    }
    lab[j] = '\0';
    return (lab);
}

int labcheck(char *str, asm_t *com)
{
    int i = 0;
    char *lab = NULL;
    char c = LABEL_CHAR;

    for (; str[i] != '\0' && str[i] != c; i++);
    if (str[i] == '\0')
        return (0);
    lab = create_labstr(str, i);
    for (int x = 0; lab[x] != '\0'; x++)
        if (check_labchar(lab[x]) == 84)
            return (0);
    for (; com->prev != NULL; com = com->prev);
    for (; com != NULL; com = com->next) {
        if (com->label != NULL && my_strcmp(com->label, lab) == 0) {
            free(lab);
            return (1);
        }
    }
    free(lab);
    return (0);
}

int check_mnemonique(int check, asm_t *commands, op_t *opstruct)
{
    for (int i = 0; opstruct[i].mnemonique != NULL; i++)
        if (my_strcmp(commands->arg, opstruct[i].mnemonique) == 0)
            check = check_struct(commands, opstruct, i);
    return (check);
}
