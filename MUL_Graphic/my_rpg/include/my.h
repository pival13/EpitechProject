/*
** EPITECH PROJECT, 2018
** my.h
** File description:
** Header of mylib
*/

#ifndef MY_H
#define MY_H

#include "enum.h"
#include "rpg.h"
#include "csfml.h"
#include "../lib/include/my.h"
#include "macro.h"

void mouse_follow(rpg_t *w);          //Common
obj_t *create_key_cursor(sfClock *clock);
void convert_binary(cell_t **map, int fd);
void convert_decimal_to_binary(map_t *map, char **map1);
equipment_t get_equipment(rpg_t *w, char *name);
void add_equipment(rpg_t *w, equipment_t equip);
void complete_players(rpg_t *w);
int get_level(int exp);
void change_page(rpg_t *w, int page);
void change_page_back(rpg_t *w);
int calculate_atk(rpg_t *, int player);
int calculate_def(rpg_t *, int player);
int calculate_res(rpg_t *, int player);
int calculate_agi(rpg_t *, int player);

void draw_main_menu(rpg_t *w);        //Main_menu
int events_main_menu(rpg_t *w);
void page_main_menu(rpg_t *w);
void animation_background_mm(rpg_t *w);
void key_cursor_main_menu(rpg_t *w);
void animation_buttons_mm(rpg_t *w);

void page_create_save(rpg_t *w);      //Save
void create_save(rpg_t *w);
void save_save(rpg_t *w);
int check_save(void);
void load_save(rpg_t *w);

void draw_settings(rpg_t *w);         //Settings
void events_settings(rpg_t *w);
void page_settings(rpg_t *w);
void key_cursor_settings(rpg_t *w);
void set_volume(rpg_t *w);

int load_equipment(rpg_t *w);        //Read_data
int load_data(rpg_t *w);
int load_stat(stat_t *stat, char *race);
int read_quest(rpg_t *w);

int create_map(rpg_t *w);              //World
int verification_map(char **map);
cell_t **load_map(char **map);
void move_map(rpg_t *w);
void move_chara(rpg_t *w);
void edit_map(rpg_t *w, float change_angle[2], float change_pos[2], flo\
at change_size);
void page_world(rpg_t *w);
void map_follow_player(rpg_t *w);

void fight(rpg_t *r);                   //fight
void check_time_fight(rpg_t *r);
int check_mp(rpg_t *r, int cost);
int fight_over(rpg_t *r);
void s_select(rpg_t *r, int nb);
void in_attack(rpg_t *r, int nb);
void select_spell(rpg_t *r);
void print_page_button(rpg_t *r, sfVector2f *pos, char **tab);
void event_page_fight(rpg_t *r);
void print_button(rpg_t *r, char **tab);
void run(rpg_t *r);
void in_attack(rpg_t *r, int which);
void give_exp(rpg_t *r);
void little_attack(rpg_t *r);
void draw_shortcut(rpg_t *r, sfVector2f *pos);
void text_draw(rpg_t *r, char *str, sfVector2f pos, sfColor color);
void place_all(rpg_t *r, int which);
void are_you_dead(rpg_t *r);
int find_scene(rpg_t *r);
void enemy(rpg_t *r);
int attack(rpg_t *r);
void print_something(rpg_t *r, char *str, sfVector2f pos);
void find_coeff(rpg_t *r, int which, int n);
void draw_rectangle(rpg_t *r, int which);
void is_end(rpg_t *r);
void ennemi_stat(rpg_t *r);
void print_button(rpg_t *r, char **tab);
void mage_d(rpg_t *r);
void invo_d(rpg_t *r);
void dwarf(rpg_t *r);
void archery_e(rpg_t *r);
void mage_e(rpg_t *r);
void archery_h(rpg_t *r);
void begin_fight(rpg_t *r, int salut, int *which);
void lancer_h(rpg_t *r);
void thief_h(rpg_t *r);
void ogre(rpg_t *r);
void weak_point(rpg_t *r);
int anim(rpg_t *r, int move);
void enemy_turn(rpg_t *r, sfVector2f pos);
void text_draw(rpg_t *r, char *str, sfVector2f pos, sfColor color);
void draw_mana(rpg_t *w);
void draw_fuite(rpg_t *w);

void animation_buttons_ig(rpg_t *w);    //In-game menu
void event_ingame_menu(rpg_t *w, int *i);
void ingame_menu(rpg_t *w, int *i);
void shop_events(rpg_t *w);

void page_quests_menu(rpg_t *w);       // Quests menu
void draw_quests_menu(rpg_t *w);
void events_quests_menu(rpg_t *w);
void animation_buttons_qm(rpg_t *w);
void key_cursor_qm(rpg_t *w);
void load_qm(rpg_t *w);
void change_title_qm_right(rpg_t *w);
void change_title_qm_left(rpg_t *w);
void set_description_qm(rpg_t *w, int pos);
void create_desc_qm(quest_m_t *qm, sfClock *clock);

void character_menu(rpg_t *w);         //Status menu
void character_menu_interactions(rpg_t *w, int *a, int *b);
void character_menu_set_sprite(rpg_t *w, int *a, int *b, sfSprite *str[11]);

void reach_place(rpg_t *w, quest_t *quest); //Quests
void have_gold(rpg_t *w, quest_t *quest);
void reach_level(rpg_t *w, quest_t *quest);
void load_quests(char **file, quest_t *quest);

void page_intro(rpg_t *w);              //Intro
void draw_intro(rpg_t *w);
void events_intro(rpg_t *w);
void dialogue_intro(rpg_t *w);
void events_choices_intro_expanded(rpg_t *w);
void set_choices_str(char *manip, char *manip1, char *manip2, char *str);

void draw_text(rpg_t *w, int a, int b);
void draw_save(rpg_t *w, int a, int b, char *str);
void display_gold(rpg_t *w);
char *convert_int_in_char(int nb);
void display_spell(rpg_t *w, int id);

#endif //_MY_H_
