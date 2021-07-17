/*
** EPITECH PROJECT, 2019
** read_quest
** File description:
** read the quest in quest.data
*/

#include "my.h"

quest_t load_quest(rpg_t *r, char **file)
{
    quest_t w;

    if (nb_row(file) < 7) {
        w.name = NULL;
        return (w);
    }
    w.name = file[0];
    w.description = file[1];
    w.gold = my_getnbr(file[2]);
    w.exp = my_getnbr(file[3]);
    w.completed = 0;
    w.equipment = get_equipment(r, file[4]);
    load_quests(file, &w);
    return (w);
}

int error_quests(void)
{
    my_dprintf(2, "quest.data is bugged/or missing.\n");
    return (84);
}

int read_quest(rpg_t *w)
{
    int len = 0;
    char ***file = cut_file("data/quest.data");

    if (!file) {
        w->qm->quests = NULL;
        return (error_quests());
    }
    for (; file[len] != NULL; len++);
    w->qm->quests = malloc(sizeof(quest_t) * (len+1));
    if (w->qm->quests == NULL)
        return (error_quests());
    for (int i = 0; i != len; i++) {
        w->qm->quests[i] = load_quest(w, file[i]);
        if (w->qm->quests[i].name == NULL)
            return (error_quests());
    }
    w->qm->quests[len].name = NULL;
    return (0);
}
