/*
** EPITECH PROJECT, 2019
** create_fight_struct.c
** File description:
** create fight struct
*/

#include "my.h"

void create_fight_struct2(fight_t *fight, sfClock *clock)
{
    fight->nomana_msg = sfSprite_create();
    fight->nomana = 0;
    fight->fuite = 0;
    fight->fuite_msg = sfSprite_create();
    fight->time_mana = create_time_obj(clock);
    fight->time_fuite = create_time_obj(clock);
}

fight_t *create_fight_struct(sfClock *clock)
{
    fight_t *fight = malloc(sizeof(fight_t));

    fight->go = 5;
    for (int i = 0; i < 13; i++)
        fight->sprite[i] = sfSprite_create();
    fight->shape = sfRectangleShape_create();
    fight->circle = sfCircleShape_create();
    fight->allies = 0;
    fight->skill = 0;
    fight->resultat = 0;
    fight->nomana = 0;
    fight->turn = -1;
    fight->choice = 0;
    fight->text = sfText_create();
    fight->cut = sfText_create();
    fight->nb_ennemies = (rand() % 5) + 1;
    for (int i = 0; i < fight->nb_ennemies; i++)
        fight->which[i] = (rand() % 19) + 41;
    create_fight_struct2(fight, clock);
    return (fight);
}

void destroy_fight_struct(fight_t *fight)
{
    for (int i = 0; i < 11; i++)
        sfSprite_destroy(fight->sprite[i]);
    sfRectangleShape_destroy(fight->shape);
    sfCircleShape_destroy(fight->circle);
    sfSprite_destroy(fight->nomana_msg);
    sfSprite_destroy(fight->fuite_msg);
    destroy_time_obj(fight->time_mana);
    destroy_time_obj(fight->time_fuite);
    sfText_destroy(fight->text);
    sfText_destroy(fight->cut);
    free(fight);
}
