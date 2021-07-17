/*
** EPITECH PROJECT, 2019
** rpg.h
** File description:
** header of my_rpg
*/

#include "my.h"

char *convert_int_in_char(int nb)
{
    char *str = NULL;
    int save = 0;
    int count = 0;

    if (nb == 0) {
        str = malloc(sizeof(char) * 2);
        str[0] = '0';
        str[1] = '\0';
        return (str);
    }
    for (save = nb; save != 0; save = save / 10, count++);
    str = malloc(sizeof(char) * (count + 1));
    count = 0;
    for (save = nb; save > 0; count++) {
        str[count] = save % 10 + 48;
        save = save / 10;
    }
    str[count] = '\0';
    str = my_revstr(str);
    return (str);
}

static void set_texte_display_stat(rpg_t *w, sfText *texte)
{
    sfText_setFont(texte, w->font);
    sfText_setCharacterSize(texte, 50);
    sfText_setColor(texte, COLOR(207, 148, 54));
}

static void display_stat2(rpg_t *w, sfVector2f move, sfText *texte, c\
har *str[16])
{
    for (int a = 0; str[a] != NULL; a++) {
        (a != 0 && a % 2 == 1) ? (move.y += 50) : ((a != 0) ?
        (move.x += sfText_getGlobalBounds(texte).width + 10) : (0));
        sfText_setPosition(texte, move);
        (a != 0 && a % 2 == 1) ? (0) : ((a != 0) ?
        (move.x -= sfText_getGlobalBounds(texte).width + 10) : (0));
        sfText_setString(texte, str[a]);
        sfRenderWindow_drawText(w->win, texte, NULL);
    }
}

static void display_stat(rpg_t *w, int id)
{
    static sfText *texte = NULL;
    char *str[16] = {w->player[id].name, "Level:          ",
    convert_int_in_char(w->player[id].level), "Health:        ",
    convert_int_in_char(w->player[id].stat.hp[0]),
    "Mana:         ", convert_int_in_char(w->player[id].stat.mp[0]),
    "Strength:     ", convert_int_in_char(calculate_atk(w, id)),
    "Defense:     ", convert_int_in_char(calculate_def(w, id)),
    "Resistance: ", convert_int_in_char(calculate_res(w, id)),
    "Agility:         ", convert_int_in_char(calculate_agi(w, id)), NULL};
    sfVector2f move = {550, 400};

    if (texte == NULL) {
        texte = sfText_create();
        set_texte_display_stat(w, texte);
    }
    display_stat2(w, move, texte, str);
    display_gold(w);
}

void character_menu(rpg_t *w)
{
    static int a = 0;
    static int b = 0;
    sfSprite *str[11] = {w->ch->deamon->sprite, w->ch->deamonf->sprite,
    w->ch->naim->sprite, w->ch->naimf->sprite, w->ch->elf->sprite,
    w->ch->elff->sprite, w->ch->human->sprite, w->ch->humanf->sprite,
    w->ch->ogre->sprite, w->ch->ogref->sprite, NULL};

    if (w->fight->resultat == 1 && KEY_R(sfKeyEscape))
        change_page(w, FIGHT);
    sfRenderWindow_drawSprite(w->win, w->ch->bgd->sprite, NULL);
    sfRenderWindow_drawSprite(w->win, w->ch->character->sprite, NULL);
    sfRenderWindow_drawSprite(w->win, w->ch->button_right->sprite, NULL);
    sfRenderWindow_drawSprite(w->win, w->ch->button_left->sprite, NULL);
    character_menu_interactions(w, &a, &b);
    character_menu_set_sprite(w, &a, &b, str);
    display_stat(w, a);
    display_spell(w, a);
}
