/*
** EPITECH PROJECT, 2019
** bonus
** File description:
** bonus of matchstick
*/

#include "my.h"
#include "matchstick.h"
#include "csfml.h"
#include <SFML/System.h>
#include <SFML/Graphics.h>

void draw_match(window_t *w, match_t m)
{
    sfVector2f pos;
    sfVector2f size;

    size.x = 0.2 * 100 / m.line;
    size.y = 0.2 * 100 / m.line;
    sfSprite_setScale(w->sprite, size);
    sfRenderWindow_clear(w->window, sfBlack);
    for (int j = 0; j != m.line; j++) {
        pos.y = j * 40*size.y + (j+1);
        for (int i = 0; i != (m.line)*2-1; i++) {
            if ((m.line-i-1) < j+1 && i+1 < (m.line+j+1) && m.map[j+1]\
[i+1] == '|') {
                pos.x = (1500 / (m.line*2-1)) * (i+0.5) - 5*size.x;
                sfSprite_setPosition(w->sprite, pos);
                sfRenderWindow_drawSprite(w->window, w->sprite, NULL);
            }
        }
    }
    return;
}

void graph_ia(match_t *m, window_t *w)
{
    int line;
    int match;
    sfClock *clock = sfClock_create();

    ia(m, &line, &match);
    draw_match(w, *m);
    sfRenderWindow_display(w->window);
    while (sfClock_getElapsedTime(clock).microseconds < 500000);
    change_map(m, line, match);
}

int main(int n, char **arg)
{
    match_t map;
    window_t *w;

    if (n != 3) return (84);
    map.map = prepare_map(my_getnbr(arg[1]));
    map.line = my_getnbr(arg[1]);
    map.match = my_getnbr(arg[2]);
    if (map.line >= 50) return (0);
    w = create_struct_window(1500, 850, "Matchstick", "bonus/match.png");
    while (match_present(map.map)) {
        if (sfRenderWindow_pollEvent(w->window, &w->event))
            if (w->event.type == sfEvtClosed)
                sfRenderWindow_close(w->window);
        draw_match(w, map);
        chose_match(&map, w);
        if (match_present(map.map) == 0)
            break;
        graph_ia(&map, w);
    }
}
