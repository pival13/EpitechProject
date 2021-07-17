/*
** EPITECH PROJECT, 2019
** create_save_page2.c
** File description:
** create save page 2
*/

#include "my.h"

static int check_time(rpg_t *w)
{
    static sfTime time = {0};

    if (time.microseconds <
        sfClock_getElapsedTime(w->clock).microseconds - 150000) {
        time = sfClock_getElapsedTime(w->clock);
        return (1);
    }
    return (0);
}

void draw_text2(rpg_t *w, int a, int b)
{
    sfText_setOrigin(w->cs->t[0],
    (sfVector2f){sfText_getGlobalBounds(w->cs->t[0]).width/2, 0});
    sfText_setColor(w->cs->t[6-w->player[a].sexe], sfRed);
    sfText_setColor(w->cs->t[7+w->player[a].classe], sfRed);
    sfText_setColor(w->cs->t[1+b], sfRed);
    for (int i = 0; i != 10; draw_sftext(w->win, w->cs->t[i++]));
    edit_text(w->cs->t[9], w->cs->class[3*a+2], 360 +
    sfText_getGlobalBounds(w->cs->t[3]).width +
    sfText_getGlobalBounds(w->cs->t[7]).width +
    sfText_getGlobalBounds(w->cs->t[8]).width, 3.05*SIZE(y)/4);
}

void draw_text(rpg_t *w, int a, int b)
{
    edit_text(w->cs->t[0], w->player[a].race, SIZE(x)/2, 50);
    edit_text(w->cs->t[1], "Sexe: ", 20, SIZE(y)/7*2.15);
    edit_text(w->cs->t[5], "Male", 390 +
    sfText_getGlobalBounds(w->cs->t[1]).width, SIZE(y)/7*2.15);
    edit_text(w->cs->t[6], "Female", 440 +
    sfText_getGlobalBounds(w->cs->t[1]).width +
    sfText_getGlobalBounds(w->cs->t[5]).width, SIZE(y)/7*2.15);
    edit_text(w->cs->t[2], "Name:", 20, 2*SIZE(y)/3.9);
    edit_text(w->cs->t[4], w->player[a].name, 310 +
    sfText_getGlobalBounds(w->cs->t[2]).width, 2 * SIZE(y)/3.9);
    edit_text(w->cs->t[3], "Class:", 20, 3*SIZE(y)/4);
    edit_text(w->cs->t[7], w->cs->class[3*a], 280 +
    sfText_getGlobalBounds(w->cs->t[3]).width, 3.05*SIZE(y)/4);
    edit_text(w->cs->t[8], w->cs->class[3*a+1], 320 +
    sfText_getGlobalBounds(w->cs->t[3]).width +
    sfText_getGlobalBounds(w->cs->t[7]).width, 3.05*SIZE(y)/4);
    draw_text2(w, a, b);
}

void draw_save2(rpg_t *w, int a, int b, char *str)
{
    sfRenderWindow_drawSprite(w->win, w->mm->bgd->sprite, NULL);
    sfRenderWindow_drawSprite(w->win, w->cs->panel->sprite, NULL);
    sfRenderWindow_drawSprite(w->win, w->cs->character, NULL);
    draw_text(w, a, b);
    (str[0] == '\0') ?
    (sfRenderWindow_drawText(w->win, w->cs->text_gte, NULL)) : (0);
    (w->cs->created->time_anim->seconds < 1) ?
    (draw_sprite(w->win, w->cs->created->sprite)) : (0);
}

void draw_save(rpg_t *w, int a, int b, char *str)
{
    int race[10] = {DEMONF, DEMONH, NAINF, NAINH,
    ELFF, ELFH, HUMANF, HUMANH, OGREF, OGREH};
    int sprite[30] = {6, 8, 0, 5, 8, 0, 7, 0, 0, 6, 0, 0, 5, 6, 0,
    5, 7, 0, 5, 5, 7, 5, 6, 6, 5, 0, 0, 5, 0, 0};
    int text = race[2*a+w->player[a].sexe] + w->player[a].classe + 1;
    sfIntRect rect = {0, 0, sfTexture_getSize(w->textures[text]).x
    / sprite[6*a+3*w->player[a].sexe+w->player[a].classe],
    sfTexture_getSize(w->textures[text]).y};
    static int i = 0;

    get_time(w->cs->created->time_anim, w->clock);
    if ((KEY(sfKeyTab) || i != 0) && check_time(w))
        i = (i +1) % sprite[6*a+3*w->player[a].sexe+w->player[a].classe];
    rect.left = rect.width*i;
    sfSprite_setTexture(w->cs->character, w->textures[text], sfTrue);
    sfSprite_setTextureRect(w->cs->character, rect);
    animation_background_mm(w);
    draw_save2(w, a, b, str);
}
