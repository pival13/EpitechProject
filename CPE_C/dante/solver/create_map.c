/*
** EPITECH PROJECT, 2019
** create_map
** File description:
** create a map
*/

#include "dante.h"

static void destroy_all(int fd)
{
    close(fd);
    exit(84);
}

void create_map(char *filepath, solver_t *map)
{
    struct stat status;
    int fd;

    fd = open(filepath, O_RDONLY);
    if (fd == -1)
        exit(84);
    if (fstat(fd, &status) == -1)
        destroy_all(fd);
    map->map = malloc(sizeof(char) * (status.st_size + 1));
    if (map->map == NULL)
        destroy_all(fd);
    if (read(fd, map->map, status.st_size) != status.st_size)
        destroy_all(fd);
    map->map[status.st_size] = '\0';
    map->finish = 0;
    close(fd);
}