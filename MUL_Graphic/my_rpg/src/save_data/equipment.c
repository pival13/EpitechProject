/*
** EPITECH PROJECT, 2019
** get_equipment
** File description:
** get the equipment with its name
*/

#include "my.h"

equipment_t get_equipment(rpg_t *w, char *name)
{
    equipment_t equip;

    equip.name = NULL;
    if (name == NULL || name[0] == '\0')
        return (equip);
    for (int i = 0; w->equip[i].name != NULL; i++) {
        if (!my_strcmp(name, w->equip[i].name))
            return (w->equip[i]);
    }
    return (equip);
}

void add_equipment(rpg_t *w, equipment_t equip)
{
    for (int i = 0; i != 50; i++)
        if (w->inventory.equip[i].name == NULL) {
            w->inventory.equip[i] = equip;
            w->inventory.equip[i+1].name = NULL;
            return;
        }
}