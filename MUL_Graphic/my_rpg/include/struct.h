/*
** EPITECH PROJECT, 2019
** rpg.h
** File description:
** header of my_rpg
*/

#ifndef MY_RPG_H_
#define MY_RPG_H_

#include "my.h"
#include "csfml.h"
#include "import.h"

typedef struct rpg_s rpg_t;

typedef struct mob_stat_s {
    int hp;
    int atk;
    int def;
    int res;
    int agi;
} mob_stat_t;

typedef struct stat_s {
    int hp[2];
    int mp[2];
    int exp;
    int atk;
    int def;
    int res;
    int agi;
} stat_t;

typedef struct equipment_s {
    int type; // head, chest, arm, leg, axe, bow, dagger, lance, staff
    char *name;
    stat_t stat;
} equipment_t;

typedef struct skill_s {
    char *name;
    char *description;
    int cooldown;
    stat_t stat;
    void (*funct)();
} skill_t;

typedef struct mob_s {
    int status;
    char *name;
    int level;
    sfTexture *texture;
    mob_stat_t stat;
} mob_t;

typedef struct player_s {
    int status;
    int nb_sprite;
    char *name;
    char *race;
    int classe;
    int cost[3];
    int sexe;
    int level;
    sfTexture *texture;
    stat_t stat;
    equipment_t equip[5];
    skill_t skill[5];
} player_t;

typedef struct quest_s {
    char *name;
    char *description;
    int gold; //reward
    int exp; //reward
    equipment_t equipment; //reward
    void (*funct)(rpg_t *, struct quest_s *); //The pointer to the funct
    int *use;
    int completed;
} quest_t;

typedef struct cell_s {
    sfVector2f pos;
    int height;
    int texture;
    int known;
} cell_t;

typedef struct map_s {
    sfConvexShape *shape;
    cell_t **map[6][4];
    quest_t *quest;
    sfVector2i pos;
    sfVector2i cur_map;
    sfSprite *diamond;
} map_t;
void destroy_map(map_t *map);

typedef struct inventory_s {
    equipment_t equip[50];
    int gold;
} inventory_t;

#endif
