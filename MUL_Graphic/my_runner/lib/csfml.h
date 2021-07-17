/*
** EPITECH PROJECT, 2018
** csfml.h
** File description:
** header of csfml
*/

#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <SFML/Audio.h>

#define SCREEN_X 800
#define SCREEN_Y 450

#ifndef CSFML_H_
#define CSFML_H_

#define USAGE "A runner game create with CSFML.\n\nUSAGE\n  ./my_runner \
[OPTION] map.txt\n\n  map.txt\tmap to load:\n\t\t  '#' is ground,\n\t\t  \
'M' is spike\n\nOPTIONS\n  -h\t\tprint this usage and quit.\n\nUSER INTERA\
CTIONS\n  SPACE_KEY\tjump.\n  ESCAPE\tclose the game.\n"
#define TEXT(title, x, y) create_text(title, x, y)

typedef enum object_type {
    SKY,
    BACKGROUND,
    PLAYER,
    DOG,
    GROUND,
    GRASS,
    SPIKE
} object_type_t;

typedef struct text_s {
    sfText *text;
    sfFont *font;
    sfVector2f origin;
    sfVector2f pos;
} text_t;

typedef struct object_s {
    sfTexture *texture;
    sfSprite *sprite;
    sfIntRect rect;
    sfVector2f pos;
    sfVector2f scale;
    int nb_pict;
    float move_speed;
    float anim_speed;
} object_t;

typedef struct map_s {
    char type;
    sfVector2f pos;
    sfVector2f move;
} map_t;

typedef struct window_s {
    sfVideoMode mode;
    sfRenderWindow *window;
    sfEvent event;
    int mouse;
    sfClock *clock;
    sfClock *jump;
    sfMusic *music;
    sfMusic *sound;
    map_t **map;
    object_t **obj;
} window_t;

window_t *create_struct_window(int width, int height, char *name, char *arg);
object_t *create_obj(char *filepath, int nb_pict, int x, int y);
text_t *create_text(char *str, int x, int y);
void draw_window(window_t *w);
map_t ** destroy_map(map_t **map);
void destroy_everything(window_t *w);
void move_obj(sfClock *clock, object_t *obj, float move_x, float move_y);
void anim_obj(sfClock *clock, object_t *obj, int start, int end);
void resize_obj(object_t *obj, float size);
void origin_obj(object_t *obj, int x, int y);
void display_loop(sfRenderWindow *window, object_t *obj);
void draw_ground(sfRenderWindow *window, object_t **obj, map_t **map);
void choose_level(window_t *w, object_t *back);
void how_to_play(window_t *w, object_t *back);
void change_color(text_t **t, int a);
void move_ground(sfRenderWindow *window, object_t **obj, map_t **map, \
sfClock *clock);
void game(window_t *w, char *name);
map_t **load_map(char *arg);
void jump_chara(sfClock *clock, window_t *w);
void fall_chara(window_t *w);
void check_end(window_t *w);

#endif //CSFMH_H_
