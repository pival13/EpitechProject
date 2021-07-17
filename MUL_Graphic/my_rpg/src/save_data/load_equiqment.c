/*
** EPITECH PROJECT, 2019
** load equipment
** File description:
** load the equipement
*/

#include "my.h"

int nb_equipment(void)
{
    int nb = 0;
    DIR *dir;
    struct dirent *content;
    char **file;

    dir = opendir("data/equipment/");
    content = readdir(dir);
    while (content != NULL) {
        file = read_file(my_merge_3("data/equipment/", content->d_name, NULL));
        nb += nb_row(file);
        for (int i = 0; file != NULL && file[i] != NULL; i++)
            free(file[i]);
        free(file);
        content = readdir(dir);
    }
    closedir(dir);
    return (nb);
}

equipment_t read_equip(char **file)
{
    equipment_t equip;

    equip.type = my_getnbr(file[0]);
    equip.name = my_strcpy(file[1]);
    equip.stat.hp[0] = my_getnbr(file[2]);
    equip.stat.mp[0] = my_getnbr(file[3]);
    equip.stat.atk = my_getnbr(file[4]);
    equip.stat.def = my_getnbr(file[5]);
    equip.stat.res = my_getnbr(file[6]);
    equip.stat.agi = my_getnbr(file[7]);
    return (equip);
}

int load_equipment2(rpg_t *w, int *j, char ***file)
{
    for (int i = 0; file[i] != NULL; i++, *j += 1) {
        w->equip[*j] = read_equip(file[i]);
    }
    return (0);
}

int load_equipment(rpg_t *w)
{
    DIR *dir = opendir("data/equipment/");
    struct dirent *cont;
    int nb = nb_equipment();
    char ***file;
    int j = 0;

    w->equip = malloc(sizeof(equipment_t) * (nb + 1));
    cont = readdir(dir);
    while (cont != NULL) {
        if (cont->d_name[0] != '.') {
            file = cut_file(my_merge_3("data/equipment/", cont->d_name, NULL));
            if (file == NULL)
                return (84);
            load_equipment2(w, &j, file);
        }
        cont = readdir(dir);
    }
    closedir(dir);
    w->equip[j].type = -1;
    return (0);
}
