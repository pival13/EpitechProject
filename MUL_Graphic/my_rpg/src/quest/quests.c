/*
** EPITECH PROJECT, 2019
** read_quest
** File description:
** read the quest in quest.data
*/

#include "my.h"

void reach_place(rpg_t *w, quest_t *quest)
{
    int *use = quest->use;

    if (w->map->cur_map.x == use[0] && w->map->cur_map.y == use[1] &&
        w->map->pos.x == use[2] && w->map->pos.y == use[3]) {
        w->inventory.gold += quest->gold;
        for (int i = 0; i != 5; i++) {
            w->player[i].stat.exp += quest->exp;
            w->player[i].level = get_level(w->player[i].stat.exp);
        }
        add_equipment(w, quest->equipment);
        quest->completed = 1;
    }
}

void have_gold(rpg_t *w, quest_t *quest)
{
    if (w->inventory.gold >= quest->use[0]) {
        w->inventory.gold += quest->gold;
        for (int i = 0; i != 5; i++) {
            w->player[i].stat.exp += quest->exp;
            w->player[i].level = get_level(w->player[i].stat.exp);
        }
        add_equipment(w, quest->equipment);
        quest->completed = 1;
    }
}

void reach_level2(rpg_t *w, quest_t *quest)
{
    for (int j = 0; j != 5; j++) {
        w->player[j].stat.exp += quest->exp;
        w->player[j].level = get_level(w->player[j].stat.exp);
    }
    add_equipment(w, quest->equipment);
}

void reach_level(rpg_t *w, quest_t *quest)
{
    for (int i = 0; i != 5; i++) {
        if (w->player[i].level >= quest->use[0]) {
            w->inventory.gold += quest->gold;
            reach_level2(w, quest);
            add_equipment(w, quest->equipment);
            quest->completed = 1;
            break;
        }
    }
}
