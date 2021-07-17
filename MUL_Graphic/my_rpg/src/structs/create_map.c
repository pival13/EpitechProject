/*
** EPITECH PROJECT, 2019
** create map
** File description:
** create the map
*/

#include "my.h"

int check_maps_exist(rpg_t *w)
{
    if (w->map->map[0][0] == NULL)
        return (0);
    for (int i = 1; i != 6; i++)
        for (int j = 0; j != 4; j++)
            if (w->map->map[i][j] == NULL)
                return (0);
    return (1);
}

int check_each_map(rpg_t *w, struct dirent *content)
{
    char *name;
    char **file;
    int len = 0;

    name = content->d_name;
    if (name[0] != '.') {
        file = read_file(my_merge_3("data/map/", name, NULL));
        if (verification_map(file))
            return (destroy_rpg_struct(w));
        len = my_strlen(name);
        if (is_int(&name[len-2]))
            w->map->map[name[len-2]-'0'+1][name[len-1]-'0'] = load_map(file);
        else
            w->map->map[0][0] = load_map(file);
        free_tab(file);
    }
    return (0);
}

int load_all_map(rpg_t *w)
{
    DIR *dir;
    struct dirent *content;

    dir = opendir("data/map/");
    if (dir == NULL)
        return (destroy_rpg_struct(w));
    content = readdir(dir);
    while (content != NULL) {
        check_each_map(w, content);
        content = readdir(dir);
    }
    closedir(dir);
    if (!check_maps_exist(w))
        return (84);
    return (0);
}

int create_map2(rpg_t *w)
{
    w->map = malloc(sizeof(map_t));
    w->map->shape = sfConvexShape_create();
    sfConvexShape_setPointCount(w->map->shape, 4);
    sfConvexShape_setOutlineColor(w->map->shape, sfColor_fromRGBA(0, 0, 0, 50));
    sfConvexShape_setOutlineThickness(w->map->shape, 1);
    sfConvexShape_setFillColor(w->map->shape, sfGreen);
    w->map->diamond = sfSprite_create();
    return (0);
}

int create_map(rpg_t *w)
{
    create_map2(w);
    w->map->pos = (sfVector2i){1, 1};
    sfSprite_setTexture(w->map->diamond, w->textures[DIAMOND], sfTrue);
    sfSprite_setScale(w->map->diamond,
    (sfVector2f){40/sfSprite_getLocalBounds(w->map->diamond).width,
    40/sfSprite_getLocalBounds(w->map->diamond).width});
    sfSprite_setOrigin(w->map->diamond,
    (sfVector2f){sfSprite_getLocalBounds(w->map->diamond).width/2,
    sfSprite_getLocalBounds(w->map->diamond).height});
    w->map->cur_map = (sfVector2i){0, 0};
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 4; w->map->map[i][j++] = NULL);
    if (load_all_map(w) == 84)
        return (84);
    edit_map(w, NULL, NULL, 0);
    return (0);
}
