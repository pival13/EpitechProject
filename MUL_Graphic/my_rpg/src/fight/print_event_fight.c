/*
** EPITECH PROJECT, 2019
** buton
** File description:
** event fight
*/

#include "my.h"

void select_spell(rpg_t *r)
{
    if (r->fight->choice == 1)
        little_attack(r);
    (r->fight->choice == 0 && r->event.key.code == sfKeyNum3 &&
    r->event.type == sfEvtKeyReleased) ? (change_page(r, CH)) : (0);
    if (r->event.key.code == sfKeyNum1 && r->event.type == sfEvtKeyReleased
        && r->fight->choice > 1) {
        r->fight->choice = 3;
    }
    (r->event.key.code == sfKeyNum2 && r->event.type == sfEvtKeyReleased
    && r->fight->choice > 1) ? (r->fight->choice = 4) : (0);
    if (r->event.key.code == sfKeyNum3 && r->event.type == sfEvtKeyReleased
        && r->fight->choice > 1)
        r->fight->choice = 5;
    (r->mob[r->fight->go].stat.hp < 0) ? (r->fight->go++) : (0);
    if (r->fight->choice != 2)
        s_select(r, r->fight->go);
}

void draw_all_spell(rpg_t *r, sfVector2f *pos, char **tab)
{
    for (int i = 0; i < 3; i++) {
        if (r->fight->choice == 2)
            text_draw(r, tab[i], pos[i], sfWhite);
        else if (r->fight->choice != i+3)
            text_draw(r, tab[i], pos[i], (sfColor){150, 150, 150, 255});
        else
            text_draw(r, tab[i], pos[i], sfWhite);
    }
}

void print_page_button(rpg_t *r, sfVector2f *pos, char **tab)
{
    sfText_setFont(r->fight->text, r->font2);
    sfText_setCharacterSize(r->fight->text, 30);
    char **base = (char *[4]){"Attack", "Skill", "Status", "Run"};

    if (r->fight->choice < 2) {
        if (r->fight->choice == 1) {
            text_draw(r, "attack", pos[0], sfWhite);
            for (int i = 1; i < 4; i++)
                text_draw(r, base[i], pos[i], (sfColor){150, 150, 150, 255});
        }
        else
            for (int i = 0; i < 4; i++)
                text_draw(r, base[i], pos[i], sfWhite);
    }
    else {
        draw_all_spell(r, pos, tab);
        text_draw(r, "Back", pos[3], sfWhite);
        }
    draw_shortcut(r, pos);
}

void event_page_fight(rpg_t *r)
{
    select_spell(r);
    if ((r->event.key.code == sfKeyNum1 && r->event.type == sfEvtKeyReleased
        && r->fight->choice == 0 && r->fight->go > 4))
        r->fight->choice = 1;
    if (r->event.key.code == sfKeyNum2 && r->event.type == sfEvtKeyReleased
        && r->fight->choice < 2)
        r->fight->choice = 2;
    if (r->event.key.code == sfKeyEscape && r->event.type == sfEvtKeyReleased
        && r->fight->choice < 2) {
        if ((rand() % 5) / 4)
            return run(r);
        else {
            r->fight->fuite = 1;
            r->fight->turn = -1;
            r->fight->choice = 0;
        }
    }
    if (r->event.key.code == sfKeyEscape && r->event.type == sfEvtKeyReleased\
&& r->fight->choice > 1)
        r->fight->choice = 0;
}

void print_button(rpg_t *r, char **tab)
{
    int last = 5 + r->fight->nb_ennemies + 1;
    sfVector2f pos[5] = {(sfVector2f){sfRenderWindow_getSize(r->win).x * 0.3 -
    sfSprite_getGlobalBounds(r->fight->sprite[last]).width,
    sfRenderWindow_getSize(r->win).y * 0.2 - sfSprite_getGlobalBounds
    (r->fight->sprite[last]).height}, (sfVector2f){sfRenderWindow_getSize
    (r->win).x * 0.6 - sfSprite_getGlobalBounds(r->fight->sprite[last]).width,
    sfRenderWindow_getSize(r->win).y * 0.2-sfSprite_getGlobalBounds
    (r->fight->sprite[last]).height}, (sfVector2f){sfRenderWindow_getSize
    (r->win).x * 0.9 - sfSprite_getGlobalBounds(r->fight->sprite[last]).width,
    sfRenderWindow_getSize(r->win).y * 0.2 -
    sfSprite_getGlobalBounds(r->fight->sprite[last]).height}, (sfVector2f)
    {sfRenderWindow_getSize(r->win).x * 0.6 - sfSprite_getGlobalBounds
    (r->fight->sprite[last]).width, sfRenderWindow_getSize(r->win).y -
    sfSprite_getGlobalBounds(r->fight->sprite[last]).height - 5}, (sfVector2f)
    {sfRenderWindow_getSize(r->win).x * 0.9 - sfSprite_getGlobalBounds
    (r->fight->sprite[last]).width, sfRenderWindow_getSize(r->win).y -
    sfSprite_getGlobalBounds(r->fight->sprite[last]).height - 5}};

    print_page_button(r, pos, tab);
    event_page_fight(r);
}
