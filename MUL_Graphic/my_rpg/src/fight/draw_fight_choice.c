/*
** EPITECH PROJECT, 2019
** draw buton
** File description:
** draw buton
*/

#include "my.h"

void draw_shortcut(rpg_t *r, sfVector2f *pos)
{
    int last = 5 + r->fight->nb_ennemies + 1;
    char **base = (char *[4]){"1", "2", "3", "Esc"};

    sfText_setFont(r->fight->cut, r->font);
    sfText_setCharacterSize(r->fight->cut, 18);
    sfText_setFillColor(r->fight->cut, sfBlack);
    for (int i = 0; i < 4; i++) {
        sfText_setString(r->fight->cut, base[i]);
        sfText_setOrigin(r->fight->cut,
        (sfVector2f){sfText_getLocalBounds(r->fight->cut).width,
        sfText_getLocalBounds(r->fight->cut).height / 2});
        sfText_setPosition(r->fight->cut,
        (sfVector2f){pos[i].x +
        sfSprite_getGlobalBounds(r->fight->sprite[last]).width / 2 + 10,
        pos[i].y + sfSprite_getGlobalBounds
        (r->fight->sprite[last]).height - 21});
        sfRenderWindow_drawText(r->win, r->fight->cut, NULL);
    }
}

void text_draw(rpg_t *r, char *str, sfVector2f pos, sfColor color)
{
    int last = 5 + r->fight->nb_ennemies + 1;

    sfSprite_setPosition(r->fight->sprite[last], pos);
    sfSprite_setColor(r->fight->sprite[last], color);
    sfSprite_setScale(r->fight->sprite[last], (sfVector2f){450 / sfSprite_getLo\
calBounds(r->fight->sprite[last]).width, 150 / sfSprite_getLocalBounds(r->fight\
->sprite[last]).height});
    sfRenderWindow_drawSprite(r->win, r->fight->sprite[last], NULL);
    sfText_setString(r->fight->text, str);
    sfText_setPosition(r->fight->text, (sfVector2f){sfSprite_getPosition(r->\
fight->sprite[last]).x + sfSprite_getGlobalBounds(r->fight->sprite[last]).width\
/ 2 - sfText_getGlobalBounds(r->fight->text).width / 2, sfSprite_getPosition\
(r->fight->sprite[last]).y + sfSprite_getGlobalBounds(r->fight->sprite[last]).\
height / 2 - sfText_getGlobalBounds(r->fight->text).height - 18});
    sfRenderWindow_drawText(r->win, r->fight->text, NULL);
}

void print_something(rpg_t *r, char *str, sfVector2f pos)
{
    static sfTime time = {0};

    if (time.microseconds == 0)
        time = sfClock_getElapsedTime(r->clock);
    if (time.microseconds + 1000000 > sfClock_getElapsedTime(r->clock).microsec\
onds) {
        text_draw(r, str, pos, sfWhite);
        return;
    }
    time.microseconds = 0;
}
