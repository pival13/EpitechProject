/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** command
*/

#include "server.h"

const char *ressources[] = {
    "food",
    "linemate",
    "deraumere",
    "sibur",
    "mendiane",
    "phiras",
    "thystame",
    NULL
};

const char *basic_command[] = {
    "Forward",
    "Right",
    "Left",
    "Look",
    "Inventory",
    "Broadcast",
    "Connect_nbr",
    "Fork",
    "Eject",
    "Take",
    "Set",
    "Incantation",
    "FakeIncantation",
    NULL
};

const float freq_basic_command[] = {
    7, 7, 7, 7, 1, 7, 0, 42, 7, 7, 7, 300, 300
};

const char *graphic_command[] = {
    "msz",
    "bct",
    "mct",
    "tna",
    "ppo",
    "plv",
    "pin",
    "sgt",
    "sst",
    NULL
};

void (*command_server[])(client_t *, server_t *) = {
    forward, right, left, look, inventory, broadcast, connect_nbr, fork_c, \
eject, take, set, incantation, fakeincantation, msz, bct, mct, tna, ppo, \
plv, pin, sgt, sst
};
