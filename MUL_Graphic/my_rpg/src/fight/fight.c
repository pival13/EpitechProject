/*
** EPITECH PROJECT, 2019
** fight
** File description:
** fight
*/

#include "my.h"

void code(rpg_t *r)
{
    are_you_dead(r);
    is_end(r);
    if (r->event.key.code == sfKeyRight && r->event.type == sfEvtKeyReleased) {
        r->fight->go += 1;
        (r->fight->go > 5+r->fight->nb_ennemies) ? (r->fight->go = 5) : 0;
    }
    if (r->event.key.code == sfKeyLeft && r->event.type == sfEvtKeyReleased) {
        r->fight->go -= 1;
        (r->fight->go < 5) ? (r->fight->go = 5+r->fight->nb_ennemies) : 0;
        while (r->mob[r->fight->go-5].stat.hp <= 0) {
            r->fight->go--;
            if (r->fight->go < 5)
                r->fight->go = 5+r->fight->nb_ennemies-1;
        }
    }
    while (r->mob[r->fight->go-5].stat.hp <= 0 && !fight_over(r)) {
        r->fight->go++;
        (r->fight->go > 5+r->fight->nb_ennemies-1) ? (r->fight->go = 5) : 0;
    }
}

void draww(rpg_t *r)
{
    int salut = 5+r->fight->nb_ennemies;

    begin_fight(r, salut, r->fight->which);
    code(r);
    attack(r);
    sfRenderWindow_display(r->win);
}

void set_texture_fight(rpg_t *r)
{
    int i = 0;

    for (int i = 0; i < 5; i++)
        sfSprite_setTexture(r->fight->sprite[i], r->player[i].texture, sfTrue);
    for (i = 5; i < 5+r->fight->nb_ennemies; i++)
        sfSprite_setTexture(r->fight->sprite[i], r->textures[r->fight->which\
[i-5]], sfTrue);
    sfSprite_setTexture(r->fight->sprite[i], r->textures[find_scene(r)], \
sfTrue);
    sfSprite_setTexture(r->fight->sprite[i+1], r->textures[86], sfTrue);
    r->fight->resultat = 1;
}

void initialize(rpg_t *r)
{
    if (r->fight->resultat == 0) {
        r->fight->nb_ennemies = (rand() % 5) + 1;
        for (int i = 0; i < r->fight->nb_ennemies; i++)
            r->fight->which[i] = (rand() % 19) + 41;
        ennemi_stat(r);
        check_time_fight(r);
        for (int i = 0; i < 10; i++) {
            r->fight->stat[i].hp = 0;
            r->fight->stat[i].atk = 0;
            r->fight->stat[i].def = 0;
            r->fight->stat[i].res = 0;
            r->fight->stat[i].agi = 0;
        }
        set_texture_fight(r);
    }
}

void fight(rpg_t *r)
{
    for (int i = 0; r->musics[i] != NULL; i++)
        if (i != 2 && sfMusic_getStatus(r->musics[i]) == sfPlaying) {
            sfMusic_stop(r->musics[i]);
            sfMusic_play(r->musics[2]);
        }
    initialize(r);
    check_time_fight(r);
    draww(r);
    draw_mana(r);
    draw_fuite(r);
}
