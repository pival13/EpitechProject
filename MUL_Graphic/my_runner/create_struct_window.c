/*
** EPITECH PROJECT, 2018
** create struct window
** File description:
** Create the struct window_t
*/

#include "my.h"
#include "csfml.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

map_t **load_map_2(map_t **map, int fd)
{
    char *line;
    int nb;

    line = get_next_line(fd);
    for (nb = 0; line != NULL; nb++) {
        map[nb] = malloc(sizeof(map_t) * (my_strlen(line) + 1));
        for (int i = 0; line[i] != '\0'; i++) {
            map[nb][i].type = line[i];
            map[nb][i].pos.x = i * 40 + 1;
            map[nb][i].pos.y = nb * 40 + 1;
            map[nb][i+1].type = '\0';
        }
        free(line);
        line = get_next_line(fd);
    }
    map[nb] = NULL;
    return (map);
}

map_t **load_map(char *arg)
{
    map_t **map = NULL;
    char *line;
    int fd = open(arg, 0, O_RDONLY);
    int nb = 0;

    if (fd == -1) return (NULL);
    line = get_next_line(fd);
    for (; line != NULL; nb++) {
        free(line);
        line = get_next_line(fd);
    }
    map = malloc(sizeof(map_t *) * (nb+1));
    close(fd);
    fd = open(arg, 0, O_RDONLY);
    if (fd == -1) return (NULL);
    load_map_2(map, fd);
    close(fd);
    return (map);
}

object_t *create_obj(char *filepath, int nb_pict, int x, int y)
{
    object_t *obj = malloc(sizeof(object_t));

    obj->texture = sfTexture_createFromFile(filepath, NULL);
    obj->sprite = sfSprite_create();
    sfSprite_setTexture(obj->sprite, obj->texture, sfFalse);
    obj->rect.top = 0;
    obj->rect.left = 0;
    obj->rect.width = sfTexture_getSize(obj->texture).x/nb_pict;
    obj->rect.height = sfTexture_getSize(obj->texture).y;
    obj->nb_pict = nb_pict;
    obj->pos.x = x;
    obj->pos.y = y;
    obj->scale.x = 1;
    obj->scale.y = 1;
    sfSprite_setPosition(obj->sprite, obj->pos);
    return (obj);
}

object_t **prepare_obj(void)
{
    object_t **obj = malloc(sizeof(object_t *) * 8);

    obj[SKY] = create_obj("sprite/sky.png", 1, 0, 0);
    obj[BACKGROUND] = create_obj("sprite/midground.png", 1, 0, 0);
    obj[PLAYER] = create_obj("sprite/gin.png", 21, 135, 1);
    obj[DOG] = create_obj("sprite/dog.png", 8, 1, 321);
    obj[GROUND] = create_obj("sprite/bloc.png", 1, 1, 1);
    obj[GRASS] = create_obj("sprite/bloc2.png", 1, 1, 1);
    obj[SPIKE] = create_obj("sprite/spike.png", 1, 1, 1);
    obj[7] = create_obj("sprite/test.png", 1, 1, 1);
    resize_obj(obj[SKY], 0.8);
    resize_obj(obj[BACKGROUND], 3.5);
    resize_obj(obj[PLAYER], 1.5);
    resize_obj(obj[DOG], 1.5);
    resize_obj(obj[GROUND], 2);
    resize_obj(obj[GRASS], 2);
    origin_obj(obj[PLAYER], 0, 100);
    origin_obj(obj[DOG], 0, 100);
    return (obj);
}

window_t *create_struct_window(int width, int height, char *name, char *arg)
{
    window_t *w = malloc(sizeof(window_t));

    w->mode.width = width;
    w->mode.height = height;
    w->mode.bitsPerPixel = 32;
    w->window = sfRenderWindow_create(w->mode, name, sfDefaultStyle, \
NULL);
    sfRenderWindow_setVerticalSyncEnabled(w->window, sfTrue);
    sfRenderWindow_setFramerateLimit(w->window, 30);
    w->jump = sfClock_create();
    w->mouse = 0;
    w->music = sfMusic_createFromFile("sprite/music.ogg");
    w->sound = sfMusic_createFromFile("sprite/sound.ogg");
    w->obj = prepare_obj();
    w->map = load_map(arg);
    sfMusic_play(w->music);
    sfMusic_setLoop(w->music, sfTrue);
    w->clock = sfClock_create();
    return (w);
}
