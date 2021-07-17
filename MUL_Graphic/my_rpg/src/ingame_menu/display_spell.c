/*
** EPITECH PROJECT, 2019
** rpg.h
** File description:
** header of my_rpg
*/

#include "my.h"

void set_str_spells3(rpg_t *w, int id, char *str[4])
{
    if (w->player[id].classe == 2 && id == 3) {
        str[0] = "Sneak\nAn attack which ignore the mob's def.\n5MP";
        str[1] = "Taste of blood\nA weak attack which causes a bleeding.\n15MP";
        str[2] = "Blood-lust\nA swift attack which increases agility.\n15MP";
    }
    if (w->player[id].classe == 0 && id == 4) {
        str[0] = "Fear\nA monstrous fist which slow the mob.\n20MP";
        str[1] = "Fury\nIncrease atk but loss life at regular\ntime.\n10MP";
        str[2] = "Cannibalism\nAttack an ally but\nincrease all your"
        "stats and heal.\n20MP";
    }
    if (w->player[id].classe == 1 && id == 3) {
        str[0] = "Barrage\nCan perform up to five consecutives lower attacks."
        "\n10MP";
        str[1] = "Piercing\nPierce the mob guard and decrease its def.\n30MP";
        str[2] = "Slash\nA strong attack which deals 120% damage.\n5MP";
    }
}

void set_str_spells2(rpg_t *w, int id, char *str[4])
{
    if (w->player[id].classe == 0 && id == 2) {
        str[0] = "Sylvan Guard\nHeals the team with 20% of atk.\n5MP";
        str[1] = "Piercing Shot\nA shot that decreases the\nmob's def and res."
        "\n15MP";
        str[2] = "Arrow's rain\nAttacks all enemies with 40% of atk.\n25MP";
    }
    if (w->player[id].classe == 1 && id == 2) {
        str[0] = "Root's trap\nWeak attack that blocks the\nenemy"
        "from attacking.\n25MP";
        str[1] = "Blossom\nAttack which improves\nallies' stats.\n25MP";
        str[2] = "Holy Blessing\nHeal the wholeteam at\nregular time.\n25MP";
    }
    if (w->player[id].classe == 0 && id == 3) {
        str[0] = "Double Shot\nAn attack which on your enemy and\nhis "
        "right neighbour.\n10MP";
        str[1] = "Weak Point\nStrike an arrow which decrease mob\ndef.\n15MP";
        str[2] = "Explosive Arrow\nStrike an explosive arrow which burn\n"
        "the mob.\n20MP";
    }
    set_str_spells3(w, id, str);
}

void set_str_spells(rpg_t *w, int id, char *str[4])
{
    if (w->player[id].classe == 0 && id == 0) {
        str[0] = "Fireball\nStrikes a fireball which deals\n80% of atk and "
        "burns the enemy.\n20MP";
        str[1] = "Electric Shot\nStrikes a fast and powerful electric\nshot "
        "which deals 130% atk.\n30MP";
        str[2] = "Life Drain\nAn attack which heals about 33% of\nall damages"
        "dealt.\n30MP";
    }
    if (w->player[id].classe == 1 && id == 0) {
        str[0] = "Magic Arrow\nDraws a magic arrow which uses\n the lowest"
        "def or res of the enemy.\n15MP";
        str[1] = "Resurrection\nResurrects a dead ally with\n half of "
        "its life.\n20MP";
        str[2] = "Leech\nSteals life of an enemy at regular\n times.\n30MP";
    } if (w->player[id].classe == 0 && id == 1) {
        str[0] = "Shield bash\nDeals lower damages but stuns the\nenemy.\n25MP";
        str[1] = "Taunt\nAn attack which increases def.\n10MP";
        str[2] = "Slaughter\nDeals a strong attack with all your\npower.\n20MP";
    }
    set_str_spells2(w, id, str);
}

void display_spell(rpg_t *w, int id)
{
    static sfText *texte = NULL;
    sfVector2f move = {1170, 400};
    char *str[4] = {"", "", "", NULL};

    if (texte == NULL) {
        texte = sfText_create();
        sfText_setFont(texte, w->font);
        sfText_setCharacterSize(texte, 40);
        sfText_setColor(texte, COLOR(207, 148, 54));
    }
    set_str_spells(w, id, str);
    for (int a = 0; str[a] != NULL; a++) {
        (a != 0) ? (move.y += 200) : (0);
        sfText_setPosition(texte, move);
        sfText_setString(texte, str[a]);
        sfRenderWindow_drawText(w->win, texte, NULL);
    }
}
