/*
** EPITECH PROJECT, 2019
** struct.h
** File description:
** main structs
*/

#ifndef STRUCT_H
#define STRUCT_H

#include "struct.h"
#include "import.h"
#include "csfml.h"

typedef struct character_s {
    obj_t *bgd;
    obj_t *character;
    obj_t *return_button;
    obj_t *elf;
    obj_t *elff;
    obj_t *deamon;
    obj_t *deamonf;
    obj_t *human;
    obj_t *humanf;
    obj_t *ogre;
    obj_t *ogref;
    obj_t *naim;
    obj_t *naimf;
    obj_t *button_right;
    obj_t *button_left;
} character_t;
character_t *create_character_ingame(sfClock *clock, sfTexture **textures);
void destroy_character_texture(character_t *ch);

typedef struct fight_s {
    mob_stat_t stat[10];
    sfSprite *sprite[15];
    sfRectangleShape *shape;
    sfCircleShape *circle;
    sfText *text;
    sfText *cut;
    sfIntRect rect;
    int resultat;
    int nb_ennemies;
    int which[5];
    int go;
    int turn;
    int choice;
    int print;
    int allies;
    int skill;
    int way;
    int nomana;
    sfSprite *nomana_msg;
    int fuite;
    sfSprite *fuite_msg;
    time_obj *time_mana;
    time_obj *time_fuite;
} fight_t;
fight_t *create_fight_struct(sfClock *clock);
void destroy_fight_struct(fight_t *fight);

typedef struct main_menu_s {
    obj_t *buttons[7];
    obj_t *bgd;
    obj_t *title;
    int play_mode;
    time_obj *click_delay;
    obj_t *key_cursor;
    int key_pos;
    obj_t *no_save;
    obj_t *deleted;
} main_menu_t;
main_menu_t *create_main_menu_struct(sfClock *clock, sfTexture **textures);
void destroy_main_menu_struct(main_menu_t *mm);

typedef struct settings_s {
    obj_t *bgd;
    obj_t *sound_icon;
    obj_t *music_icon;
    obj_t *sound_bar[10];
    obj_t *music_bar[10];
    obj_t *return_button;
    int sound_volume;
    int music_volume;
    obj_t *key_cursor;
    int key_pos;
} settings_t;
settings_t *create_settings_struct(sfClock *clock, sfTexture **textures);
void destroy_settings_struct(settings_t *sett);

typedef struct ingame_s {
    obj_t *bgd;
    obj_t *buttons[5];
    obj_t *message_save;
    int key_pos;
    int key_pos2;
    obj_t *shop[5];
    obj_t *bought;
    obj_t *no_money;
} ingame_t;
ingame_t *create_ingame_menu_struct(sfClock *clock, sfTexture **textures);
void destroy_ingame_menu_struct(ingame_t *ig);

typedef struct quest_m_s {
    quest_t *quests;
    obj_t *bgd;
    obj_t *switch_buttons[2];
    obj_t *switch_name_buttons[2];
    obj_t *return_button;
    obj_t *quests_name[3];
    obj_t *title;
    int key_pos;
    time_obj *click_delay;
    int title_pos;
    obj_t *desc;
    obj_t *gold;
    obj_t *exp;
    obj_t *item;
    obj_t *status;
} quest_m_t;
quest_m_t *create_quest_menu_struct(sfClock *clock, sfTexture **textures);
void destroy_quest_menu_struct(quest_m_t *qm);

typedef struct c_save_s {
    obj_t *panel;
    sfSprite *character;
    sfText *t[10];
    char *class[15];
    sfText *text_gte;
    obj_t *created;
} c_save_t;
c_save_t *create_cs_struct(sfClock *cl, sfTexture **te, sfFont *f, sfFont *f2);
void destroy_cs_struct(c_save_t *cs);

typedef struct intro_s {
    sfFont *font;
    sfText *dialogue;
    sfText *choices[3];
    obj_t *key_cursor;
    obj_t *bgd;
    obj_t *bgd2;
    obj_t *narrator;
    int key_pos;
    int end;
    int speaking;
    obj_t *f_dialogue;
    obj_t *f_choices;
    char **dialogue_tab;
    char **choices_tab;
    sfText *point;
    time_obj *point_delay;
    int step;
} intro_t;
intro_t *create_intro_struct(sfClock *clock, sfTexture **te);
void destroy_intro_struct(intro_t *intro);

typedef struct rpg_s {
    obj_t *cursor;
    int page;
    int old_page;
    main_menu_t *mm;
    settings_t *sett;
    ingame_t *ingame;
    quest_m_t *qm;
    c_save_t *cs;
    intro_t *intro;
    sfClock *clock;
    sfTime time;
    equipment_t *equip;
    inventory_t inventory;
    player_t player[5];
    mob_t mob[5];
    map_t *map;
    sfTexture **textures; //all texture
    sfMusic **sounds;
    sfMusic **musics;
    sfFont *font;
    sfFont *font2;
    sfRenderWindow *win;
    sfVideoMode mode;
    fight_t *fight;
    character_t *ch;
    sfEvent event;
    int key_mode;
    int pause_mode[7];
    int evb;
} rpg_t;
rpg_t *create_rpg_struct(void);
int destroy_rpg_struct(rpg_t *w);
int create_texture_tab(rpg_t *w);
int create_sounds_and_musics_tab(rpg_t *w);

#endif
