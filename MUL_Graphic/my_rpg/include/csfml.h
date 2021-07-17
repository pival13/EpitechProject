/*
** EPITECH PROJECT, 2019
** csfml.h
** File description:
** csfml functs header
*/

#ifndef CSFML_H
#define CSFML_H

#include "import.h"

typedef struct collision_t {
    float x01;
    float x02;
    float x11;
    float x12;
    float y01;
    float y02;
    float y11;
    float y12;
} collision_t;

typedef struct radius_coll {
    float radius;
    float rx;
    float ry;
    float x1;
    float y1;
    float x2;
    float y2;
} radius_coll;

typedef struct time_obj {     //Time structure
    sfTime time;
    float seconds_init;
    float seconds;
} time_obj;
time_obj *create_time_obj(sfClock *clock);
void destroy_time_obj(time_obj *time);
void reset_time(time_obj *time, sfClock *clock);
void end_pause_time(time_obj *time, sfClock *clock);
float get_time(time_obj *time, sfClock *clock);

typedef struct lib_sprite_t {
    sfSprite **sprites;
    sfTexture **textures;
} lib_sprite_t;

typedef struct obj_t {
    char *content;              //If the object is a text.
    sfText *text;
    sfFont *font;
    unsigned int chsize;

    sfSound *sound;             //Sounds & music.
    sfSoundBuffer *buffer;
    sfMusic *music;

    sfSprite *sprite;           //Sprites & textures.
    sfTexture *texture;

    time_obj *time_move;        //Common properties.
    time_obj *time_anim;
    sfVector2f origin;
    sfIntRect rect;
    sfVector2f pos;
    sfVector2f scale;
    int anim_mode;
} obj_t;
obj_t *create_obj_t_sprite(sfClock *clock, char *sprite, sfTexture *texture);
obj_t *create_obj_t_text(sfClock *clock, char *text, char *font_path);
obj_t *create_obj_t_sound(sfClock *clock, char *sound_path);
obj_t *create_obj_t_music(sfClock *clock, char *sound_path);
void obj_init(obj_t *obj);
void destroy_obj_t(obj_t *obj);

void mod_color(sfSprite *sprite, float re, float gr, float bl);
void mod_scale(obj_t *obj, float n);
void mod_scale_p(obj_t *obj, float n);

void set_visible(sfSprite *sprite);
void set_invisible(sfSprite *sprite);
void set_alpha(sfSprite *sprite, float alpha);
void obj_set_position(obj_t *obj, float x, float y);
void obj_move(obj_t *obj, float x, float y);
void obj_set_position_text(obj_t *obj, float x, float y);
void obj_move_text(obj_t *obj, float x, float y);

int collision_entities(obj_t *obj1, obj_t *obj2);
int collision_cursor(obj_t *cursor, obj_t *obj);

int activate_animation(obj_t *obj, sfClock *clock);
int deactivate_animation(obj_t *obj, sfClock *clock);

void center_obj(obj_t *obj);
int anim_sprite(obj_t *obj, int sens, int ite);
int set_anim_sprite(obj_t *obj, int sens, int ite);
// int sens : horizontal = 0, vertical = 1
// int ite : iterations dans l'animation

int click_button(obj_t *cursor, obj_t *button, sfEvent event);

void animation_prog_scale(obj_t *obj, sfClock *c, float max, float speed);
int cut_animation(obj_t *obj, int x, int y);

void draw_sprite(sfRenderWindow *win, sfSprite *sprite);
void draw_sftext(sfRenderWindow *win, sfText *text);

void sprite_set_scale(sfSprite *sprite, float x, float y);
void sprite_set_origin(sfSprite *sprite, float x, float y);
void sprite_set_position(sfSprite *sprite, float x, float y);

sfText *create_text(char *str, int size, sfFont *font);
void edit_text(sfText *t, char *str, float x, float y);

int collision_cursor_text(obj_t *cursor, sfText *obj);
int click_button_text(obj_t *cursor, sfText *button, sfEvent event);

void sprite_move(sfSprite *sprite, float x, float y);
void edit_text_color(sfText *t, float r, float g, float b);
void edit_text_str(sfText *t, char *str);

#endif
