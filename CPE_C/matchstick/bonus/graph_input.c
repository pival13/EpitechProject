/*
** EPITECH PROJECT, 2019
** graph_input
** File description:
** Get the input of the player in the graphical game
*/

#include "my.h"
#include "matchstick.h"
#include "csfml.h"
#include <SFML/System.h>
#include <SFML/Graphics.h>

int get_line_graph(window_t *w, match_t *m, rect_t *r)
{
    sfRenderWindow_pollEvent(w->window, &w->event);
    draw_match(w, *m);
    r->pos.y = w->event.mouseMove.y / (int)r->size.y * (r->size.y+1) + 1;
    sfRectangleShape_setPosition(r->rect, r->pos);
    sfRenderWindow_drawRectangleShape(w->window, r->rect, NULL);
    sfRenderWindow_display(w->window);
    if (w->event.type == sfEvtClosed) return (0);
    if (w->event.type == sfEvtMouseButtonPressed)
        return (sfMouse_getPositionRenderWindow(w->window).y / (int)r->size\
.y + 1);
    return (0);
}

int get_match_graph(window_t *w, match_t *m, rect_t *r, int line)
{
    int p = (1500 / (m->line*2-1)) * (m->line-line + get_nb_matches(m->map\
[line]));

    draw_match(w, *m);
    r->pos.x = w->event.mouseMove.x / (1500/(m->line*2-1)) * (1500/(m->line\
*2-1));
    if (p - r->pos.x < 1500/(m->line*2-1))
        r->pos.x = p - 1500/(m->line*2-1);
    if (p - r->pos.x > 1500/(m->line*2-1) * SMALLEST())
        r->pos.x = p - 1500/(m->line*2-1) * SMALLEST();
    r->size.x = p - r->pos.x;
    sfRectangleShape_setSize(r->rect, r->size);
    sfRectangleShape_setPosition(r->rect, r->pos);
    sfRenderWindow_drawRectangleShape(w->window, r->rect, NULL);
    sfRenderWindow_display(w->window);
    sfRenderWindow_pollEvent(w->window, &w->event);
    if (w->event.type == sfEvtClosed) return (0);
    if (w->event.type == sfEvtMouseButtonPressed)
        return (r->size.x) / (1500/(m->line*2-1));
    return (0);
}

void chose_match(match_t *m, window_t *w)
{
    int line = 0;
    int match = 0;
    rect_t r;

    r.rect = sfRectangleShape_create();
    r.size.x = 1500;
    r.size.y = sfSprite_getGlobalBounds(w->sprite).height;
    r.color.a = 100;
    r.pos.x = 1;
    sfRectangleShape_setFillColor(r.rect, r.color);
    sfRectangleShape_setSize(r.rect, r.size);
    while (line < 1 || line > m->line)
        line = get_line_graph(w, m, &r);
    while (w->event.type == sfEvtMouseButtonPressed)
            sfRenderWindow_pollEvent(w->window, &w->event);
    r.pos.y = (line-1) * (r.size.y+1)+1;
    while (match == 0)
        match = get_match_graph(w, m, &r, line);
    change_map(m, line, match);
}
