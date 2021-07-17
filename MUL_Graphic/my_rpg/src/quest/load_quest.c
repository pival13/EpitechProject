/*
** EPITECH PROJECT, 2019
** read_quest
** File description:
** read the quest in quest.data
*/

#include "my.h"

int *set_quest_use(int nb, ...)
{
    va_list list;
    int *use = malloc(sizeof(int) * (nb+1));

    va_start(list, nb);
    for (int i = 0; i != nb; i++)
        use[i] = va_arg(list, int);
    va_end(list);
    use[nb] = -1;
    return (use);
}

void load_quests2(char **file, quest_t *w)
{
    if (my_getnbr(file[5]) == 2) {
        if (nb_row(file) != 7) {
            w->name = NULL;
            return;
        }
        w->funct = reach_level;
        w->use = set_quest_use(1, my_getnbr(file[6]));
    }
}

void load_quests(char **file, quest_t *w)
{
    if (my_getnbr(file[5]) == 0) {
        if (nb_row(file) != 10) {
            w->name = NULL;
            return;
        }
        w->funct = reach_place;
        w->use = set_quest_use(4, my_getnbr(file[6]), my_getnbr(file[7]),
        my_getnbr(file[8]), my_getnbr(file[9]));
    } else if (my_getnbr(file[5]) == 1) {
        if (nb_row(file) != 7) {
            w->name = NULL;
            return;
        }
        w->funct = have_gold;
        w->use = set_quest_use(1, my_getnbr(file[6]));
    } else
        load_quests2(file, w);
}
