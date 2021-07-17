/*
** EPITECH PROJECT, 2019
** main
** File description:
** main of my_world
*/

#include "my.h"

static void initialize_text_map(rpg_t *w, sfText **t, sfRectangleShape **rect)
{
    *rect = sfRectangleShape_create();
    sfRectangleShape_setSize(*rect, (sfVector2f){550, 190});
    sfRectangleShape_setFillColor(*rect, COLORA(95, 138, 190, 50));
    sfRectangleShape_setOutlineColor(*rect, COLORA(207, 148, 54, 100));
    sfRectangleShape_setOutlineThickness(*rect, 3);
    sfRectangleShape_setPosition(*rect, (sfVector2f){3, 3});
    *t = sfText_create();
    sfText_setFont(*t, w->font);
    sfText_setString(*t, " Arrow keys\t\t\t\t: Move players\n ZQSD\t\t\t\t\t\t\
: Rotate map\n +/-\t\t\t\t\t\t\t  : Zoom/Dezoom\n Shift + Arrow keys\t : Move \
map\n Enter\t\t\t\t\t\t : Switch World/Area view\n ESC\t\t\t\t\t\t   : Menu");
    sfText_setCharacterSize(*t, 25);
    sfText_setColor(*t, COLOR(207, 148, 54));
    sfText_setPosition(*t, (sfVector2f){3, 3});
}

static void print_text_map(rpg_t *w)
{
    static sfText *t = NULL;
    static sfRectangleShape *rect = NULL;

    if (t == NULL)
        initialize_text_map(w, &t, &rect);
    sfRenderWindow_drawRectangleShape(w->win, rect, NULL);
    sfRenderWindow_drawText(w->win, t, NULL);
}

void print_each_cell(rpg_t *w, int i, int j)
{
    sfColor color[8] = {COLOR(150, 230, 255), COLOR(100, 0, 0), COLOR(50, 200\
, 0), COLOR(0, 100, 20), COLOR(100, 100, 100), COLOR(200, 200, 200), COLOR(150\
, 170, 70), COLOR(75, 75, 75)};
    cell_t **map = w->map->map[w->map->cur_map.y][w->map->cur_map.x];

    if (map[i][j+1].height != -100 && map[i+1] != NULL) {
        sfConvexShape_setPoint(w->map->shape, 0, map[i][j].pos);
        sfConvexShape_setPoint(w->map->shape, 1, map[i+1][j].pos);
        sfConvexShape_setPoint(w->map->shape, 2, map[i+1][j+1].pos);
        sfConvexShape_setPoint(w->map->shape, 3, map[i][j+1].pos);
        if (w->map->cur_map.y == 0 && map[i][j].known == 0)
            sfConvexShape_setFillColor(w->map->shape, color[7]);
        else
            sfConvexShape_setFillColor(w->map->shape, color[map[i][j].texture]);
        sfRenderWindow_drawConvexShape(w->win, w->map->shape, NULL);
        if (w->map->pos.y == i && w->map->pos.x == j)
            sfRenderWindow_drawSprite(w->win, w->map->diamond, NULL);
    }
}

void world(rpg_t *w)
{
    move_map(w);
    if (KEY(sfKeyReturn) && w->map->cur_map.y == 0) {
        w->map->cur_map.x = w->map->pos.x/5;
        w->map->cur_map.y = w->map->pos.y/5 + 1;
        w->map->pos.x = w->map->pos.x % 5 * 5 + 2;
        w->map->pos.y = w->map->pos.y % 5 * 5 + 2;
        edit_map(w, NULL, NULL, 0);
    } else if (KEY(sfKeyReturn)) {
        w->map->pos.x = w->map->pos.x/5 + 5*w->map->cur_map.x;
        w->map->pos.y = w->map->pos.y/5 + 5*(w->map->cur_map.y-1);
        w->map->cur_map.x = 0;
        w->map->cur_map.y = 0;
        edit_map(w, NULL, NULL, 0);
    }
    if (w->event.key.shift == sfFalse)
        move_chara(w);
}

void page_world(rpg_t *w)
{
    static int i = 0;
    cell_t **map;

    for (int i = 0; w->musics[i] != NULL; i++)
        if (i != 1 && sfMusic_getStatus(w->musics[i]) == sfPlaying) {
            sfMusic_stop(w->musics[i]);
            sfMusic_play(w->musics[1]);
        }
    sfRenderWindow_clear(w->win, COLOR(150, 230, 255));
    if (KEY(sfKeyEscape))
        i = (i + 1) % 2;
    if (i == 0)
        world(w);
    map = w->map->map[w->map->cur_map.y][w->map->cur_map.x];
    for (int i = 0; map[i] != NULL; i++)
        for (int j = 0; map[i][j].height != -100; j++)
            print_each_cell(w, i, j);
    print_text_map(w);
    if (i == 1)
        ingame_menu(w, &i);
}
