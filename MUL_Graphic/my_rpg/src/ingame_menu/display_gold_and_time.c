/*
** EPITECH PROJECT, 2019
** rpg.h
** File description:
** header of my_rpg
*/

#include "my.h"

static void set_texte_display_time(rpg_t *w, sfText *texte)
{
    sfText_setFont(texte, w->font);
    sfText_setCharacterSize(texte, 50);
    sfText_setColor(texte, COLOR(207, 148, 54));
}

static void display_time(int heure, int minute, int seconde, rpg_t *w)
{
    char *str[9] = {"Time" , ":" , convert_int_in_char(heure), ":",
    convert_int_in_char(minute), ":", convert_int_in_char(seconde), NULL};
    static sfText *texte = NULL;
    sfVector2f move = {500, 950};

    if (texte == NULL) {
        texte = sfText_create();
        set_texte_display_time(w, texte);
    }
    for (int a = 0; str[a] != NULL; a++) {
        if (a == 0)
            move.x += 35;
        else if (a == 1)
            move.x += 120;
        else
            move.x += 60;
        sfText_setPosition(texte, move);
        sfText_setString(texte, str[a]);
        sfRenderWindow_drawText(w->win, texte, NULL);
    }
}

static void calcule_time(rpg_t *w)
{
    int time = (sfClock_getElapsedTime(w->clock).microseconds +
    w->time.microseconds) / 1000000;
    int heure = 0;
    int minute = 0;
    int seconde = 0;

    while (time != 0) {
        if (time - 3600 >= 0) {
            time -= 3600;
            heure++;
        } if (time - 60 >= 0) {
            time -= 60;
            minute++;
        }
        if (time - 1 >= 0) {
            time -= 1;
            seconde++;
        }
    }
    display_time(heure, minute, seconde, w);
}

void display_gold(rpg_t *w)
{
    static sfText *texte = NULL;
    sfVector2f move = {410, 900};
    char *str[3] = {"Gold: ", convert_int_in_char(w->inventory.gold)
    , NULL};
    if (texte == NULL) {
        texte = sfText_create();
        sfText_setFont(texte, w->font);
        sfText_setCharacterSize(texte, 50);
        sfText_setColor(texte, COLOR(207, 148, 54));
    }
    for (int a = 0; str[a] != NULL; a++) {
        move.x += 130;
        sfText_setPosition(texte, move);
        sfText_setString(texte, str[a]);
        sfRenderWindow_drawText(w->win, texte, NULL);
    }
    calcule_time(w);
}
