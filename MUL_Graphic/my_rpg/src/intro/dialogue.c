/*
** EPITECH PROJECT, 2019
** dialogue.c
** File description:
** dialogue
*/

#include "my.h"

void set_dialogue_parse(rpg_t *w, char *str)
{
    char *manip = malloc(sizeof(char) * my_strlen(str) * 2);

    for (int i = 0; i < my_strlen(str) * 2 - 1; i++)
        manip[i] = 0;
    for (int i = 0, j = 0; str[i] != 0; i++, j++) {
        manip[j] = str[i];
        if (i % 77 == 0 && i != 0) {
            j++;
            manip[j] = '-';
            j++;
            manip[j] = '\n';
            j++;
            manip[j] = '-';
        }
    }
    edit_text_str(w->intro->dialogue, manip);
    free(manip);
}

void set_choices_parse(rpg_t *w, char *str)
{
    char *manip = malloc(sizeof(char) * my_strlen(str));
    char *manip1 = malloc(sizeof(char) * my_strlen(str));
    char *manip2 = malloc(sizeof(char) * my_strlen(str));

    for (int i = 0; i < my_strlen(str) - 1; manip[i++] = 0) {
        manip1[i] = 0;
        manip2[i] = 0;
    }
    set_choices_str(manip, manip1, manip2, str);
    edit_text_str(w->intro->choices[0], manip);
    edit_text_str(w->intro->choices[1], manip1);
    edit_text_str(w->intro->choices[2], manip2);
    free(manip);
    free(manip1);
    free(manip2);
}

void set_text_dialogue_intro(rpg_t *w)
{
    static char *str = NULL;
    int i = w->intro->step;

    if (w->intro->dialogue_tab[i] == NULL)
        w->page = MAP;
    else if (str == NULL || str != w->intro->dialogue_tab[i]) {
        set_dialogue_parse(w, w->intro->dialogue_tab[i]);
    }
}

void set_text_choices_intro(rpg_t *w)
{
    static char *str = NULL;
    int i = w->intro->step;

    if (w->intro->choices_tab[i] == NULL) {
        edit_text_str(w->intro->choices[0], "");
        edit_text_str(w->intro->choices[1], "");
        edit_text_str(w->intro->choices[2], "");
        w->page = MAP;
    } else if (str == NULL || str != w->intro->choices_tab[i]) {
        set_choices_parse(w, w->intro->choices_tab[i]);
    }
}

void dialogue_intro(rpg_t *w)
{
    static int status = 0;

    (w->intro->speaking == 1) ? (set_text_dialogue_intro(w))
    : (set_text_choices_intro(w));
    get_time(w->intro->point_delay, w->clock);
    if (w->intro->speaking == 1 && status == 0 &&
        w->intro->point_delay->seconds > 0.8) {
        edit_text_str(w->intro->point, "...");
        reset_time(w->intro->point_delay, w->clock);
        status = 1;
    }
    if (w->intro->speaking == 1 && status == 1 &&
        w->intro->point_delay->seconds > 0.8) {
        edit_text_str(w->intro->point, "");
        reset_time(w->intro->point_delay, w->clock);
        status = 0;
    }
}
