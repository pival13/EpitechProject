/*
** EPITECH PROJECT, 2019
** load_save
** File description:
** load a save if it exist
*/

#include "my.h"

int check_save(void)
{
    int fd = open(".sav", O_RDONLY);
    char ***file;

    if (fd == -1)
        return (0);
    close(fd);
    file = cut_file_char(".sav", '\b');
    if (nb_row(file[0]) != 6 || nb_row(file[1]) != 22 || nb_row(file[2]) != 8
        || nb_row(file[3]) != 8 || nb_row(file[4]) != 8 || nb_row(file[5]) != 8
        || nb_row(file[6]) != 8)
        return (0);
    for (int i = 0; i != 22; i++)
        if (!is_int(file[1][i]) || my_getnbr(file[1][i]) > 131071)
            return (0);
    return (1);
}

void load_save_2(rpg_t *w, char **file, int i)
{
    w->player[i].name = file[0];
    w->player[i].sexe = (my_getnbr(file[1]) > 0) ? 1 : 0;
    w->player[i].classe = (my_getnbr(file[1]) > 0) ? my_getnbr(file[1])-1
    : my_getnbr(file[1])*-1-1;
    w->player[i].stat.exp = my_getnbr(file[2]);
    for (int j = 0; j != 5; j++)
        w->player[i].equip[j] = get_equipment(w, file[3+j]);
}

void load_save(rpg_t *w)
{
    char ***file = cut_file_char(".sav", '\b');

    w->time.microseconds = my_getnbr(file[0][0]) * 1000;
    w->inventory.gold = my_getnbr(file[0][1]);
    w->map->cur_map.x = my_getnbr(file[0][2]);
    w->map->cur_map.y = my_getnbr(file[0][3]);
    w->map->pos.x = my_getnbr(file[0][4]);
    w->map->pos.y = my_getnbr(file[0][5]);
    convert_decimal_to_binary(w->map, file[1]);
    for (int i = 0; i != 5; i++)
        load_save_2(w, file[2+i], i);
    for (int i = 0; file[7] != NULL && file[7][i] != NULL && w->qm->quests[i].\
name != NULL; i++)
        w->qm->quests[i].completed = my_getnbr(file[7][i]);
    complete_players(w);
}

void save_save(rpg_t *w)
{
    int fd = open(".sav", O_TRUNC | O_CREAT | O_WRONLY, 436);

    my_dprintf(fd, "%d%c%d%c%d%c%d%c%d%c%d\n",
    (sfClock_getElapsedTime(w->clock).microseconds + w->time.microseconds)
    / 1000, '\b', w->inventory.gold, '\b', w->map->cur_map.x,
    '\b', w->map->cur_map.y, '\b', w->map->pos.x, '\b', w->map->pos.y);
    convert_binary(w->map->map[0][0], fd);
    for (int i = 0; i != 5; i++) {
        my_dprintf(fd, "%s%c%d%c%d", w->player[i].name, '\b',
        (w->player[i].classe+1)*(2*w->player[i].sexe-1), '\b',
        w->player[i].stat.exp);
        for (int j = 0; j != 5; j++)
            my_dprintf(fd, "%c%s", '\b', w->player[i].equip[j].name);
        my_dprintf(fd, "\n");
    }
    for (int i = 0; w->qm->quests[i].name != NULL; i++) {
        my_dprintf(fd, "%d%c", w->qm->quests[i].completed, '\b');
    }
    my_dprintf(fd, "\n");
    close(fd);
}

void create_save(rpg_t *w)
{
    w->inventory.gold = 100;
    w->time = sfClock_getElapsedTime(w->clock);
    w->map->cur_map = (sfVector2i){1, 3};
    w->map->pos = (sfVector2i){7, 2};
    for (int i = 0; i != 5; i++) {
        w->player[i].stat.exp = 0;
        for (int j = 0; j != 5; j++)
            w->player[i].equip[j].name = NULL;
    }
    complete_players(w);
    save_save(w);
    w->page = INTRO;
}
