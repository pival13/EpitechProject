/*
** EPITECH PROJECT, 2018
** main
** File description:
** main of my_runner
*/

#include "my.h"
#include "csfml.h"

int check_event(window_t *w)
{
    while (sfRenderWindow_pollEvent(w->window, &w->event)) {
        if (w->event.type == sfEvtClosed || (w->event.type == sfEvtKeyPressed \
&& w->event.key.code == sfKeyEscape))
            return (1);
        if (w->event.key.code == sfKeySpace && w->mouse == 0) {
            w->mouse = 1;
            sfMusic_play(w->sound);
        }
    }
    return (0);
}

void draw_window(window_t *w)
{
    display_loop(w->window, w->obj[SKY]);
    display_loop(w->window, w->obj[BACKGROUND]);
    draw_ground(w->window, w->obj, w->map);
    sfRenderWindow_drawSprite(w->window, w->obj[PLAYER]->sprite, NULL);
    sfRenderWindow_display(w->window);
    sfRenderWindow_clear(w->window, sfBlack);
}

int make_game(window_t *w)
{
    move_ground(w->window, w->obj, w->map, w->clock);
    move_obj(w->clock, w->obj[BACKGROUND], -40, 0);
    move_obj(w->clock, w->obj[SKY], -20, 0);
    jump_chara(w->jump, w);
    fall_chara(w);
    check_end(w);
    if (w->mouse == 0)
        fall_chara(w);
    if (w->mouse == 0)
        anim_obj(w->clock, w->obj[PLAYER], 1, 8);
    draw_window(w);
    if (check_event(w) == 1)
        return (1);
    else
        return (0);
}

void game(window_t *w, char *name)
{
    w->obj[PLAYER]->pos.y = 1;
    sfClock_restart(w->clock);
    w->map = load_map(name);
    if (w->map == NULL)
        return;
    while (w->map[(int)w->obj[PLAYER]->pos.y/40][4].type == ' ' || w->map  \
[(int)w->obj[PLAYER]->pos.y/40][4].type == '\0')
        w->obj[PLAYER]->pos.y += 40;
    while (sfRenderWindow_isOpen(w->window)) {
        if (make_game(w) == 1)
            return;
    }
}
