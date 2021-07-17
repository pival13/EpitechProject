/*
** EPITECH PROJECT, 2019
** anim
** File description:
** animation of fight
*/

#include "my.h"

void move_closer_enemy(rpg_t *r, sfVector2f pos_init, sfTime goal)
{
    sfVector2f enemy_pos = sfSprite_getPosition(r->fight->sprite[r->fight->go]);
    sfVector2f move = {0, 0};

    move.x = pos_init.x + ((enemy_pos.x-sfSprite_getGlobalBounds
    (r->fight->sprite[r->fight->turn]).width)
    - pos_init.x) * (sfClock_getElapsedTime(r->clock).microseconds -
    (goal.microseconds - 1000000)) / 600000;
    move.y = pos_init.y + (enemy_pos.y - pos_init.y) *
    (sfClock_getElapsedTime(r->clock).microseconds -
    (goal.microseconds - 1000000)) / 600000;
    sfSprite_setPosition(r->fight->sprite[r->fight->turn], move);
}

void anim_chara2(rpg_t *r, int *a, sfTime goal, sfTime time)
{
    sfIntRect rect = {0, 0, 0, 0};

    if (sfClock_getElapsedTime(r->clock).microseconds > goal.microseconds - 10\
00000 + (*a+1) * time.microseconds)
        *a += 1;
    rect.width = sfTexture_getSize(r->player[r->fight->turn].texture).x
    / r->player[r->fight->turn].nb_sprite;
    rect.height = sfTexture_getSize(r->player[r->fight->turn].texture).y;
    rect.left = rect.width * *a;
    rect.top = 0;
    sfSprite_setTextureRect(r->fight->sprite[r->fight->turn], rect);
}

void anim_chara(rpg_t *r, sfTime goal)
{
    static int a = -1;
    static sfTime time = {0};

    if (goal.microseconds - sfClock_getElapsedTime(r->clock).microseconds < 40\
0000 && goal.microseconds - sfClock_getElapsedTime(r->clock).microseconds > 39\
0000 && sfMusic_getStatus(r->sounds[S_FIGHT]) != sfPlaying)
        sfMusic_play(r->sounds[S_FIGHT]);
    if (a == -1 && goal.microseconds >
        sfClock_getElapsedTime(r->clock).microseconds + 200000) {
        a = 0;
        time.microseconds = 800000 / r->player[r->fight->turn].nb_sprite;
    } else if (a == -1 || goal.microseconds <
        sfClock_getElapsedTime(r->clock).microseconds + 200000) {
        a = -1;
        return;
    }
    anim_chara2(r, &a, goal, time);
}

void move_further_enemy(rpg_t *r, sfVector2f pos_init, sfTime goal)
{
    sfVector2f enemy_pos = sfSprite_getPosition(r->fight->sprite[r->fight->go]);
    sfVector2f move = {0, 0};

    move.x = enemy_pos.x - sfSprite_getGlobalBounds
    (r->fight->sprite[r->fight->turn]).width -
    ((enemy_pos.x-sfSprite_getGlobalBounds
    (r->fight->sprite[r->fight->turn]).width) - pos_init.x)
    * ((sfClock_getElapsedTime(r->clock).microseconds - 600000)
    - (goal.microseconds - 1000000)) / 400000;
    move.y = enemy_pos.y - (enemy_pos.y - pos_init.y) *
    ((sfClock_getElapsedTime(r->clock).microseconds - 600000) -
    (goal.microseconds - 1000000)) / 400000;
    sfSprite_setPosition(r->fight->sprite[r->fight->turn], move);
}

int anim(rpg_t *r, int move)
{
    static sfVector2f pos_init = {0, 0};
    static sfTime goal = {0};

    if (goal.microseconds == 0) {
        goal.microseconds = sfClock_getElapsedTime(r->clock).microseconds
        + 1000000;
        pos_init = sfSprite_getPosition(r->fight->sprite[r->fight->turn]);
    }
    if (move && goal.microseconds >
        sfClock_getElapsedTime(r->clock).microseconds + 400000)
        move_closer_enemy(r, pos_init, goal);
    else if (move)
        move_further_enemy(r, pos_init, goal);
    anim_chara(r, goal);
    sfRenderWindow_drawSprite(r->win, r->fight->sprite[r->fight->turn], NULL);
    if (goal.microseconds < sfClock_getElapsedTime(r->clock).microseconds) {
        goal.microseconds = 0;
        return (1);
    }
    return (0);
}
