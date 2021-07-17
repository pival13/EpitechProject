/*
** EPITECH PROJECT, 2019
** create_lemin_t
** File description:
** create the struct lemin_t
*/

#include "my.h"
#include "lemin.h"

void draw_beginning(char **input)
{
    int i = 1;

    my_printf("#number_of_ants\n%s\n#rooms\n", input[0]);
    for (; is_room(input[i]); i++) {
        if (i == 1)
            my_printf("##start\n");
        else if (i == 2)
            my_printf("##end\n");
        my_printf("%s\n", input[i]);
    }
    my_printf("#tunnels\n");
    for (; is_tunnel(input[i]); i++)
        my_printf("%s\n", input[i]);
    my_printf("#moves\n");
}

void destroy_input(char **input)
{

}

int start_tunnel(char **input)
{
    int nb = 0;

    for (; is_tunnel(input[nb]) == 0; nb++);
    return (nb);
}

char *name_input(char *input)
{
    int i = 0;
    char *name;

    for (; is_alphanum(input[i]); i++);
    name = malloc(sizeof(char) * (i+1));
    for (int j = 0; j != i; j++)
        name[j] = input[j];
    name[i] = '\0';
    return (name);
}

lemin_t *create_lemin_t(char **input)
{
    lemin_t *w = malloc(sizeof(lemin_t));
    room_t *room = create_room(&input[1], &input[start_tunnel(input)]);

    if (w == NULL || room == NULL)
        return (NULL);
    w->nb_ant = my_getnbr(input[0]);
    w->start_room = room;
    w->end_room = find_room(room, name_input(input[2]), 0);
    w->tab_room = malloc(sizeof(room_t *) * (start_tunnel(input)));
    if (w->tab_room == NULL)
        return (NULL);
    for (int i = 1; is_room(input[i]); i++)
        w->tab_room[i-1] = find_room(room, name_input(input[i]), 0);
    w->tab_room[start_tunnel(input)-1] = NULL;
    draw_beginning(input);
    destroy_input(input);
    return (w);
}
