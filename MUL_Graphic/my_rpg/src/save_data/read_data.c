/*
** EPITECH PROJECT, 2019
** read data
** File description:
** read the data to the struct
*/

#include "my.h"

int load_stat(stat_t *stat, char *race)
{
    char **file = read_file(my_merge_3("data/", race, "/stat.data"));

    if (file == NULL || my_arraylen(file) != 6)
        return (84);
    stat->hp[1] = my_getnbr(file[0]);
    stat->mp[1] = my_getnbr(file[1]);
    stat->exp = 0;
    stat->atk = my_getnbr(file[2]);
    stat->def = my_getnbr(file[3]);
    stat->res = my_getnbr(file[4]);
    stat->agi = my_getnbr(file[5]);
    return (0);
}

int load_data(rpg_t *w)
{
    char *race[5] = {"demon", "dwarf", "elf", "human", "ogre"};

    for (int i = 0; i != 5; i++) {
        w->player[i].race = race[i];
        w->player[i].classe = 0;
        w->player[i].sexe = 0;
        w->player[i].name = NULL;
        if (load_stat(&w->player[i].stat, race[i]) == 84)
            return (84);
        w->player[i].level = 0;
    }
    w->inventory.equip[0].name = NULL;
    w->inventory.gold = 0;
    w->event.key.shift = sfFalse;
    if (load_equipment(w) == 84)
        return (84);
    return (0);
}
