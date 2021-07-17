/*
** EPITECH PROJECT, 2020
** Created by theo on 20/06/2020.
** File description:
** struct.h
*/

#ifndef SERVER_STRUCT_H
#define SERVER_STRUCT_H

typedef struct com_pile_s com_pile_t;
typedef struct game_s game_t;
typedef struct player_s player_t;
typedef struct client_s client_t;
typedef struct tile_s tile_t;
typedef struct game_part_s game_part_t;
typedef player_t *(*fct)(player_t *client, game_t **game);
typedef struct teams_s teams_t;
typedef struct graphics_s graphics_t;
typedef struct map_s map_t;
typedef enum egg_e egg_n;

enum egg_e{
    WAS,
    IS,
    NOT,
};

///stack command
struct com_pile_s{
    char *command;

    com_pile_t *next;
};

///partie jeu client type IA

struct game_part_s{
    int team;
    char *uuid;
    char *id_inc;

    int posX;
    int posY;
    int orientation;
    int level;
    int cpt;
    int inventory[7];
    int cooldown;

    egg_n is_egg;
    fct funct;
};

/// client type IA

struct player_s {
    int fd;

    char *buffer;
    char *response;
    char *error;

    bool dead;

    game_part_t *game;

    com_pile_t *pile;

    player_t *next;
};

///client sans type

struct client_s {
    int fd;

    char *buffer;
    char *response;
    char *error;
    char *repo;

    bool delete;

    client_t *next;
};

///client graphique

struct graphics_s {
    int fd;
    char *buffer;
    char *response;
    char *error;

    bool delete;

    com_pile_t *pile;

    graphics_t *next;
};

///teams

struct teams_s {
    char *name;
    int limit;
    int nbr;

    teams_t *next;
};

///case map

struct tile_s {
    int resource[7];
};

struct map_s {
    int X;
    int Y;
    tile_t **tiles;
};

struct game_s {
    int clientNB;
    int freq;
    int port;
    int teamnb;

    int listener;

    int max;
    fd_set read_fds;
    fd_set write_fds;

    bool is_end;
    struct timeval tv;
    map_t *map;
    client_t *client;
    player_t *player;
    graphics_t *graph;
    teams_t *teams;
};

#endif //SERVER_STRUCT_H
