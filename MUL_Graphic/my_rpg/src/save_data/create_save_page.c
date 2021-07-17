/*
** EPITECH PROJECT, 2019
** create_save_page
** File description:
** create the save by asking for data
*/

#include "my.h"

void change_int(rpg_t *w, int *i, int max, int b)
{
    if (KEY(sfKeyRight))
        *i = (*i + 1) % max;
    else if (KEY(sfKeyLeft))
        *i = (*i - 1 + max) % max;
    if ((click_button_text(w->cursor, w->cs->t[5], w->event) && b == 0) ||
        (click_button_text(w->cursor, w->cs->t[8], w->event) && b == 2))
        *i = 1;
    if ((click_button_text(w->cursor, w->cs->t[6], w->event) && b == 0) ||
        (click_button_text(w->cursor, w->cs->t[7], w->event) && b == 2))
        *i = 0;
    if (click_button_text(w->cursor, w->cs->t[9], w->event) && b == 2)
        *i = 2;
}

void get_text_entered(rpg_t *w, char *str)
{
    int len = my_strlen(str);

    if (KEY(sfKeyBack) && len > 0)
        str[len-1] = '\0';
    else if (w->event.type == sfEvtTextEntered &&
    len < 18 && !(TEXT('\r') || TEXT('\b') || TEXT(27))) {
        str[len] = w->event.text.unicode;
        str[len + 1] = '\0';
    }
}

void cursor_page_create_save(rpg_t *w, int *a, int *b)
{
    if (KEY(sfKeyUp))
        *b = (*b - 1 + 3) % 3;
    else if (KEY(sfKeyDown))
        *b = (*b + 1) % 3;
    if (KEY(sfKeyReturn) && w->player[*a].name[0] != '\0') {
        *a += 1;
        reset_time(w->cs->created->time_anim, w->clock);
    }
    if (click_button_text(w->cursor, w->cs->t[1], w->event) ||
        click_button_text(w->cursor, w->cs->t[5], w->event) ||
        click_button_text(w->cursor, w->cs->t[6], w->event))
        *b = 0;
    if (click_button_text(w->cursor, w->cs->t[2], w->event) ||
        click_button_text(w->cursor, w->cs->text_gte, w->event))
        *b = 1;
    if (click_button_text(w->cursor, w->cs->t[3], w->event) ||
        click_button_text(w->cursor, w->cs->t[7], w->event) ||
        click_button_text(w->cursor, w->cs->t[8], w->event) ||
        click_button_text(w->cursor, w->cs->t[9], w->event))
        *b = 2;
}

void page_create_save(rpg_t *w)
{
    static int a = 0;
    static int b = 0;
    int class[5] = {2, 1, 2, 3, 1};

    if (a == 5) {
        a = 0;
        return (create_save(w));
    }
    if (w->player[a].name == NULL) {
        w->player[a].name = malloc(sizeof(char) * 19);
        w->player[a].name[0] = '\0';
    }
    draw_save(w, a, b, w->player[a].name);
    cursor_page_create_save(w, &a, &b);
    (b == 0) ? (change_int(w, &w->player[a].sexe, 2, b)) : (0);
    (b == 1) ? (get_text_entered(w, w->player[a].name)) : (0);
    (b == 2) ? (change_int(w, &w->player[a].classe, class[a], b)) : (0);
    (KEY_R(sfKeyEscape)) ? (b = 0, a = 0) : (0);
    if (w->event.type == sfEvtKeyPressed || w->event.type == sfEvtTextEntered)
        w->event.type = 1;
}
