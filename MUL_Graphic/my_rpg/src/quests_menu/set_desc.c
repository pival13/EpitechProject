/*
** EPITECH PROJECT, 2019
** set_desc.c
** File description:
** set desc xd
*/

#include "my.h"

char *check_desc_qm(char *str)
{
    char *desc = malloc(sizeof(char) * (my_strlen(str) * 2));

    for (int i = 0, j = 0; str[i] != 0; i++, j++) {
        desc[j] = str[i];
        if (j % 130 == 0 && j != 0) {
            j++;
            desc[j] = '\n';
        }
        desc[j+1] = 0;
    }
    return (desc);
}

char *check_gold_qm(int gold_n)
{
    char *nb = my_atoi(gold_n);
    char *gold = str_add("Gold : ", nb);

    return (gold);
}

char *check_exp_qm(int exp_n)
{
    char *nb = my_atoi(exp_n);
    char *exp = str_add("EXP : ", nb);

    return (exp);
}

char *check_item_qm(char *name)
{
    char *item;

    if (name != NULL && name[0] != 0) {
        (name[0] >= 'a' && name[0] <= 'z') ? (name[0] -= 32) : (0);
        item = str_add("Equipement : ", name);
    } else {
        item = malloc(sizeof(char));
        item[0] = 0;
    }
    return (item);
}

void set_description_qm(rpg_t *w, int pos)
{
    quest_t quest = w->qm->quests[pos];
    char *desc = check_desc_qm(quest.description);
    char *gold = check_gold_qm(quest.gold);
    char *exp = check_exp_qm(quest.exp);
    char *item = check_item_qm(quest.equipment.name);
    char *status;

    if (quest.completed == 0) {
        status = "Status : In progress";
    } else
        status = "Status : Accomplished";
    sfText_setString(w->qm->desc->text, desc);
    sfText_setString(w->qm->gold->text, gold);
    sfText_setString(w->qm->exp->text, exp);
    sfText_setString(w->qm->item->text, item);
    sfText_setString(w->qm->status->text, status);
    free(desc);
    free(gold);
    free(exp);
    free(item);
}
