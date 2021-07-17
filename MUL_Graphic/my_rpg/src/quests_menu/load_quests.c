/*
** EPITECH PROJECT, 2019
** load_quests.c
** File description:
** load quests
*/

#include "my.h"

char *check_quest_name(char *s)
{
    char *new_str;

    if (s == NULL || s[0] == 0)
        return (NULL);
    new_str = malloc(sizeof(char) * (my_strlen(s) + 1 + my_strlen(s)));
    for (int i = 0, j = 0; s[i] != 0; i++, j++) {
        new_str[j] = s[i];
        if (i % 15 == 0 && i != 0) {
            new_str[j + 1] = '-';
            j += 2;
            new_str[j] = '\n';
        }
        new_str[j+1] = 0;
    }
    if (new_str[my_strlen(new_str) - 1] == '\n') {
        new_str[my_strlen(new_str) - 1] = 0;
        (my_strlen(new_str) >= 2) ? (new_str[my_strlen(new_str) - 1] = 0) : (0);
    }
    return (new_str);
}

void set_quests_name(rpg_t *w, char *st1, char *st2, char *st3)
{
    char *s1 = check_quest_name(st1);
    char *s2 = check_quest_name(st2);
    char *s3 = check_quest_name(st3);

    if (s1 != NULL) {
        sfText_setString(w->qm->quests_name[0]->text, s1);
    } else
        sfText_setString(w->qm->quests_name[0]->text, "");
    if (s2 != NULL) {
        sfText_setString(w->qm->quests_name[1]->text, s2);
    } else
        sfText_setString(w->qm->quests_name[1]->text, "");
    if (s3 != NULL) {
        sfText_setString(w->qm->quests_name[2]->text, s3);
    } else
        sfText_setString(w->qm->quests_name[2]->text, "");
    (s1 != NULL) ? (free(s1)) : (0);
    (s2 != NULL) ? (free(s2)) : (0);
    (s3 != NULL) ? (free(s3)) : (0);
}

void load_qm(rpg_t *w)
{
    int pos = w->qm->title_pos;
    int qu_len = 0;
    char *names[3] = {NULL, NULL, NULL};

    for (qu_len = 0; w->qm->quests[qu_len].name != NULL; qu_len++);
    if (pos == 0) {
        names[1] = w->qm->quests[pos].name;
        if (qu_len != 1 && w->qm->quests[pos + 1].name != NULL)
            names[2] = w->qm->quests[pos + 1].name;
    } else if (pos > 0 && pos < qu_len - 1) {
        names[0] = w->qm->quests[pos - 1].name;
        names[1] = w->qm->quests[pos].name;
        if (qu_len != 1 && w->qm->quests[pos + 1].name != NULL)
            names[2] = w->qm->quests[pos + 1].name;
    } else {
        names[0] = w->qm->quests[pos - 1].name;
        names[1] = w->qm->quests[pos].name;
    }
    set_quests_name(w, names[0], names[1], names[2]);
    set_description_qm(w, pos);
}

void change_title_qm_right(rpg_t *w)
{
    int qu_len = 0;

    for (qu_len = 0; w->qm->quests[qu_len].name != NULL; qu_len++);
    w->qm->title_pos += 1;
    if (w->qm->title_pos >= qu_len - 1)
        w->qm->title_pos = qu_len - 1;
    load_qm(w);
}

void change_title_qm_left(rpg_t *w)
{
    w->qm->title_pos -= 1;
    if (w->qm->title_pos < 0)
        w->qm->title_pos = 0;
    load_qm(w);
}
