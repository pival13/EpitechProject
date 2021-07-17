/*
** EPITECH PROJECT, 2019
** attack
** File description:
** ennemy
*/

#include "my.h"

void enemy(rpg_t *r)
{
    int last = 5 + r->fight->nb_ennemies + 1;
    sfVector2f pos[2] = {(sfVector2f){sfRenderWindow_getSize(r->win).x * 0.3 -
    sfSprite_getGlobalBounds(r->fight->sprite[last]).width,
    sfRenderWindow_getSize(r->win).y * 0.2 - sfSprite_getGlobalBounds
    (r->fight->sprite[last]).height}, (sfVector2f){sfRenderWindow_getSize
    (r->win).x * 0.6 - sfSprite_getGlobalBounds
    (r->fight->sprite[last]).width, sfRenderWindow_getSize(r->win).y * 0.2
    - sfSprite_getGlobalBounds(r->fight->sprite[last]).height}};

    sfText_setFont(r->fight->text, r->font2);
    sfText_setCharacterSize(r->fight->text, 30);
    enemy_turn(r, pos[1]);
}

int attack(rpg_t *r)
{
    void (*skills[])(rpg_t *) = {mage_d, invo_d, dwarf, dwarf, dwarf, dwarf, \
archery_e, mage_e, dwarf, archery_h, lancer_h, thief_h, ogre};
    in_attack(r, r->fight->turn);
    if (r->fight->turn > 4) {
        enemy(r);
    }
    else if (r->fight->turn != -1)
        skills[3 * r->fight->turn + r->player[r->fight->turn].classe](r);
    return 0;
}
