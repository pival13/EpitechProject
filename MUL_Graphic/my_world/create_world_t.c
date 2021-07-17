/*
** EPITECH PROJECT, 2019
** create_map
** File description:
** error gestion
*/

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include "my.h"
#include "my_world.h"

int verification_map(char **world)
{
    int nb_pipe = 0;
    int comp_pipe = 0;

    if (world == NULL)return 1;
    for (int i = 0; world[0][i] != '\0'; i++)if (world[0][i] == '|')nb_pipe++;
    for (int i = 0; world[i] != NULL; i++) {
        comp_pipe = 0;
        for (int j = 0; world[i][j] != '\0'; j++) {
            if (world[i][j] == '|')comp_pipe++;
            else if ((world[i][j] > '9' || world[i][j] < '0') && world[i][j] !=\
'.' && world[i][j] != '-')
                return 1;
        }
        if (comp_pipe != nb_pipe)return 1;
    }
    return 0;
}

void create_map2(world_t *w)
{
    w->mode = (sfVideoMode){800, 600, 32};
    w->font = sfFont_createFromFile("sprite/Water Park.ttf");
    create_texture(w);
    w->circle = sfCircleShape_create();
    sfCircleShape_setRadius(w->circle, 20);
    sfCircleShape_setTexture(w->circle, w->texture[6], sfTrue);
    sfCircleShape_setOrigin(w->circle, (sfVector2f){20, 20});
    w->window = sfRenderWindow_create(w->mode, "My world", sf\
DefaultStyle, NULL);
    sfRenderWindow_setFramerateLimit(w->window, 60);
    sfRenderWindow_setVerticalSyncEnabled(w->window, sfTrue);
}

world_t *create_map(char *str)
{
    if (str == NULL)return NULL;
    world_t *w = malloc(sizeof(world_t));
    char **world = read_file(str);
    if (verification_map(world) == 1) world = NULL;
    if (world == NULL || w == NULL)return NULL;
    create_map2(w);
    load_map(w, world);
    create_page(w);
    w->music[0] = sfMusic_createFromFile("sprite/music.ogg");
    w->music[1] = sfMusic_createFromFile("sprite/sound.ogg");
    sfMusic_setVolume(w->music[0], 10);
    sfMusic_setVolume(w->music[1], 100);
    sfMusic_setLoop(w->music[0], sfTrue);
    sfMusic_play(w->music[0]);
    return w;
}
