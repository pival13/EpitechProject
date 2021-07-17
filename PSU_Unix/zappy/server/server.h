/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** server
*/

/**
* @file server.h
* @author Adrien, Quentin
* @brief Header du serveur.
* @version 0.1
* @date 2020-06-17
* @copyright Copyright (c) 2020
*/

#ifndef SERVER_H_
#define SERVER_H_

/* Include for Json parser */
#include "json.h"

/* Generic includes */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <stddef.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <error.h>

/* Include to handle signals */

#include <signal.h>

/* Inlcudes to create and handle sockets */

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdbool.h>

#undef EXIT_FAILURE
#define EXIT_FAILURE 84
#define EXIT_SUCCESS 0
#define LIMIT_BUFFER 1024
#define REFILL 14
#define GRAPHIC_NAME "GRAPHIC"
#define JSON_PATH "zappySettings.json"
#define LINEMATE 0
#define DERAUMERE 1
#define SIBUR 2
#define MENDIANE 3
#define PHIRAS 4
#define THYSTAME 5

typedef enum direction_s {
    UP,
    RIGHT,
    LEFT,
    DOWN
}direction_t;

/**
* @brief All types of ressources
*
*/

typedef struct ressources_s {
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
}ressources_t;

/**
* @brief All informations about a client.
* @param next Pointer to the next client.
* @param id Unique id of the client.
* @param command_array Array that contains all the client's command.
* @param buffer String that is going to be written in the client's socket.
* @param team_name String that correspond to the team's name of the client.
* @param readbuffer String that contains one command at a time.
* @param pending_command String that contains all the command that has not
* been executed yet.
* @param cooldown Float that correspond to the lapse of time before a
* command is going to be executed.
* @param food_time Float that correspond to the life span of one entity
* of food.
* @param ressources Client's inventory.
* @param direc Client's orientation.
* @param socket Client's file descriptor.
* @param lvl Client's level, which start at 1 and finish at 8.
* @param x Client's column position in the map.
* @param y Client's line position in the map.
* @param food Number of food.
* @param graphic Is client a graphic one.
* @param is_free Is client dead.
* @param egg Is client was previously an egg.
* @param is_connect True if user is connecting.
*/

typedef struct client_s {
    struct client_s *next;
    unsigned long int id;
    char *command_array[10];
    char *buffer;
    char *team_name;
    char *readbuffer;
    char *pending_command;
    int incantation[6];
    float cooldown;
    float food_time;
    ressources_t ressources;
    direction_t direc;
    int socket;
    int lvl;
    int x;
    int y;
    int food;
    bool graphic;
    bool is_free;
    bool egg;
    bool is_connect;
    bool is_incantating;
}client_t;

/**
* @brief Contains all paramaters about the game given by the user.
* @param name List team names.
* @param port Port on which the server is accessible.
* @param width Width of the map.
* @param height Height of the map.
* @param client_number Maximum number of clients allowed to be connected
* inside the same team.
* @param freq Number of actions excuted inside one second.
*/

typedef struct args_s {
    char **name;
    int port;
    int width;
    int height;
    int client_number;
    int freq;
}arg_t;

/**
* @brief Link list which contains all informations about eggs.
* @param next Ptr to the next egg.
* @param team_name String that correspond to the team's name of the client.
* @param cooldown The time it takes for the egg to hatchs.
* @param x Column on which the egg has been dropped.
* @param y Line on which the egg has been dropped.
*/

typedef struct egg_s {
    struct egg_s *next;
    char *team_name;
    float cooldown;
    unsigned long int id;
    unsigned long int id_parent;
    int x;
    int y;
}egg_t;

/**
* @brief Contains all informations about a cell's map
* @param socket_list Contains the file descriptor of each users who currently
* is on the map's cell.
* @param nb_clients The number of client who is currently present of
* the map's cell.
* @param food_number The number of food which is currently present of
* the map's cell.
* @param ressources Contains all ressources which currently are present
* of map's cell.
*/

typedef struct map_s {
    int *socket_list;
    int nb_clients;
    int food_number;
    ressources_t ressources;
}map_t;

/**
* @brief Contains all informations about the current game.
* @param client Link list that contains all the clients.
* @param map Game's map.
* @param json Contains all the json's file information.
* @param address Struct which contains the server's settings.
* @param time Time structures.
* @param readfds Contains the file descriptor of each readable client's
* socket.
* @param writefds Contains the file descriptor of each writeable client's
* socket.
* @param master_socket The file descriptor of the serer.
*/

typedef struct server_s {
    client_t *client;
    map_t **map;
    egg_t *egg;
    json_t *json;
    struct sockaddr_in address;
    struct timeval time;
    arg_t args;
    fd_set readfds;
    fd_set writefds;
    float refill_cooldown;
    int master_socket;
}server_t;

/**
* @brief Global varibale which contains references to all the parsing's
* functions
*
*/
extern int (*args_parser[])(int, char **, server_t *);

/**
* @brief Global Varibale that contains all the server parmaters's name.
*
*/
extern const char *args[];

/**
* @brief Global Variable that is used to stop the server in case of a brutal
* interruption
*
*/
extern volatile int stop;

/**
* @brief Global variable which contains all the client's commands.
*
*/
extern const char *basic_command[];

/**
* @brief Global varibale which contains all the graphical's command
* currently available.
*
*/
extern const char *graphic_command[];

/**
* @brief Global varibale which contains all the command's cooldown
* currently available.
*
*/
extern const float freq_basic_command[];

/**
* @brief Global varibale which contains all the command's
* currently available.
*
*/
extern void (*command_server[])(client_t *, server_t *);

/**
* @brief Global variable which contains all the ressources's name
* currently available.
*
*/
extern const char *ressources[];

/* Map function */

void refill_map(server_t *server);
void add_linemate(map_t *map, int *);
void add_linemate_simple(map_t *map);
void add_deraumere(map_t *map, int *);
void add_deraumere_simple(map_t *map);
void add_mendiane(map_t *map, int *);
void add_mendiane_simple(map_t *map);
void add_phiras(map_t *map, int *);
void add_phiras_simple(map_t *map);
void add_sibur(map_t *map, int *);
void add_sibur_simple(map_t *map);
void add_thystame(map_t *map, int *);
void add_thystame_simple(map_t *map);
void init_map(server_t *server);

/* Take function */

int take_ressources_last(client_t *client, server_t *server, char *str);
int take_ressources(client_t *client, server_t *server, char *str);
int take_ressources_next(client_t *client, server_t *server, char *str);
int take_set_ressources(client_t *client, server_t *server, char *str);

/* Broadcast function */

char *get_text_to_broadcast(char *command);
char *create_message(char *arg, char *dir);
float calc(int s_x, int s_y, int r_x, int r_y);
int found_x(client_t sender, client_t receiver, int width);
int found_y(client_t sender, client_t receiver, int height);
short calc_direction(server_t *server, client_t *sender, client_t *receiver);


/* Pars function */

void pars_get_number(server_t *server, json_t *);
int handle_args(server_t *server, char **av);
int check_args(server_t *server);
int basic_args(int i, char **av, server_t *server);
int clients_nb(int, char **, server_t *);
int width(int, char **, server_t *);
int height(int, char **, server_t *);
int name_x(int, char **, server_t *);
int port(int, char **, server_t *);
int freq(int, char **, server_t *);

/* Utiles function */

char **str_to_word_array(char *str, char *delimiter);
char *my_int_to_char(int num);
int hmitt(server_t *server, client_t *client);
unsigned long int max_in_team(void);
size_t size_array(char **array);
int my_const_strcmp(char *str, const char *str2);
int my_strcmp(char *str, char *str2);
int my_strlen(char *str);
bool verify_command_exist(char *str, bool graphic);
bool team_name_not_found(char *str, char **array);
bool found_separator(char *str, char c);
bool is_equal(char *str, char *str2);
bool is_digit(char *str);
void my_strcat(char **str, const char *str2);
void free_array(char **array);

/* Free server function */

void free_struct(server_t *server);
void free_map(server_t *server);

/* Graphicals function */

bool end_of_game(server_t *server);
void send_broadcast_to_graphic(server_t *server, client_t *client, char *arg);
void send_new_client_to_graphical(server_t *server, client_t *client);
void launch_graphic_command(client_t **client, server_t *server);
void send_to_all_graphic(client_t *client, char *str);

/* Incentation function */

client_t *found_client_with_fd(server_t *server, int fd);
bool prerequisite(server_t *server, client_t *client, json_t *json, int level);
bool verify_all_key(server_t *server, client_t *client);
bool new_prerequisite(server_t *server, client_t *client, json_t *json, \
int lvl);
void send_to_all_concerned_client(server_t *server, client_t *client, \
char *value);
void send_incantation_first_part(server_t *server, client_t *client);
void fakeincantation(client_t *, server_t *);
void bc_send_invocation_client(server_t *server, client_t *client, \
int nb_player);

/* Link list functons */

void free_link_list(server_t *server, bool all);
void add_node_back(client_t **client, int new_socket);

/* Server function */

int handle_select(server_t *server);
int init_server(server_t *server);
void server_loop(server_t *server);
void handle_fd(server_t *server);

/* Client function */

void write_answer_for_graphic(client_t *cli, server_t *server);
void spawn_client(server_t *server, client_t **client);
void life_gestion(server_t *server, client_t *client);
void delete_client(map_t *node, int fd);
void add_client(map_t *node, int fd);

/* Write function */

void write_all(server_t *server);
void send_client(client_t *client, char *str);
void send_broadcast(client_t *client, char *message, int fd);

/* Command gestion functions */

float command_cooldown(char *str);
void launch_command(client_t **client, server_t *server);
void remove_first_command(server_t *server, client_t *client, int freq);
void add_command(client_t **client, server_t *server);
void exec_each_command(server_t *server);
void get_command(server_t *server);
void handle_command(client_t *tmp);

/* Egg functions */

bool egg_connection(server_t *server, client_t **client);
void send_egg_laying(server_t *server, client_t *client);
void delete_egg(egg_t *egg, egg_t **egg_list, bool all);
void death_egg(server_t *server, client_t *client);
void egg_time_gestion(server_t *server);
void send_egg_laid_informations(server_t *server, egg_t *egg, \
unsigned long int id);
void send_egg_hacthing_graphical(server_t *server, unsigned long int id);

/* Connection function */

void welcome_function(client_t **cli, server_t *server);
void handle_new_connection(server_t *server);

/* Command_look_tools */
int check_map_y(int y, client_t *client, server_t *server);
int check_map_x(int x, client_t *client, server_t *server);
int set_x_pos(int turn, int x, int i, client_t *client);
int set_y_pos(int turn, int y, int i, client_t *client);

/* Move function */

void ppo_answer(client_t *client, char **str);

/* command_server */

void pic(server_t *server, map_t map, int level, client_t *client);
void bct(client_t *client, server_t *server);
void broadcast(client_t *client, server_t *server);
void connect_nbr(client_t *client, server_t *server);

/* Eject function */

int dir_bc(int dir_r, int dir);
void send_eject_bc(client_t *client, int dir_s);
void eject(client_t *client, server_t *server);

/* Forward function */
void move_left(server_t *server, client_t *client);
void move_right(server_t *server, client_t *client);
void move_up(server_t *server, client_t *client);
void move_down(server_t *server, client_t *client);

void fork_c(client_t *client, server_t *server);
void forward(client_t *client, server_t *server);
void incantation(client_t *client, server_t *server);
void inventory(client_t *client, server_t *server);
void left(client_t *client, server_t *server);
void look(client_t *client, server_t *server);
void mct(client_t *client, server_t *server);
void msz(client_t *client, server_t *server);
void pin(client_t *client, server_t *server);
void plv(client_t *client, server_t *server);
void ppo(client_t *client, server_t *server);
void right(client_t *client, server_t *server);
void set(client_t *client, server_t *server);
void sgt(client_t *client, server_t *server);
void sst(client_t *client, server_t *server);
void take(client_t *client, server_t *server);
void tna(client_t *client, server_t *server);

#endif /* !SERVER_H_ */