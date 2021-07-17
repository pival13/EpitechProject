/*
** EPITECH PROJECT, 2019
** parsing
** File description:
** parsing
*/

#include "my.h"

static void parse_label_comment_command(asm_t *r, char *str)
{
    if (my_strcmp_n(COMMENT_CMD_STRING, str, 0)) {
        r->arg = my_strcpy_not_unsigned(str);
        r->other = 2;
    } else {
        if (verify_word(str)) {
            r->other = 0;
            label(r, str);
        }
        else {
            r->other = 0;
            com(r, str);
        }
    }
}

static void parse_line(asm_t *r, char *str)
{
    if (str == NULL)
        return;
    if (str[0] == COMMENT_CHAR) {
        r->other = -1;
    } else if (my_strcmp_n(NAME_CMD_STRING, str, 0)) {
        r->arg = my_strcpy_not_unsigned(str);
        r->other = 1;
    } else
        parse_label_comment_command(r, str);
}

char *delete_chara(char *str, int j)
{
    for (; str[j] != '\0'; j++)
        str[j] = str[j+1];
    str[j] = '\0';
    return str;
}

char **reorganize_tab(char **tab)
{
    int j = 0;

    for (int i = 0; tab[i] != NULL; i++) {
        tab = delete_bad_character(tab, i, j);
        while (tab[i][0] == ' ')
            delete_chara(tab[i], 0);
        space_gestion(tab, i, j);
    }
    return tab;
}

asm_t *parsing(char **tab)
{
    asm_t *list = NULL;
    asm_t *temp = NULL;
    asm_t *memory = NULL;

    tab = reorganize_tab(tab);
    for (int i = 0; tab[i] != NULL; i++) {
        list = initialize();
        if (i == 0)
            memory = list;
        parse_line(list, tab[i]);
        list->prev = temp;
        list->next = temp;
        temp = list;
    }
    rev_list(&list);
    return (memory);
}
