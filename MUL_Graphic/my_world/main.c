/*
** EPITECH PROJECT, 2019
** main
** File description:
** main of my_world
*/

#include "my.h"
#include "my_world.h"

void menu(world_t *w, int *type)
{
    page_t p = w->page[0];

    sfRenderWindow_drawSprite(w->window, p.background, NULL);
    sfRenderWindow_drawText(w->window, p.text[0], NULL);
    sfRenderWindow_drawText(w->window, p.text[1], NULL);
    if (passed_text(w, p.text[2]) == 1) {
        sfMusic_play(w->music[1]);
        *type = 1;
    }
    if (passed_text(w, p.text[3]) == 1) {
        sfMusic_play(w->music[1]);
        *type = -1;
    }
    sfRenderWindow_drawText(w->window, p.text[2], NULL);
    sfRenderWindow_drawText(w->window, p.text[3], NULL);
    sfRenderWindow_display(w->window);
    sfRenderWindow_clear(w->window, sfWhite);
}

void print_map(world_t *w)
{
    for (int i = 0; w->map[i] != NULL; i++)
        for (int j = 0; w->map[i][j].height != -100; j++)
            if (w->map[i][j+1].height != -100 && w->map[i+1] != NULL)
                sfRenderWindow_drawConvexShape(w->window, w->map[i]\
[j].shape, NULL);
    for (int i = 1; w->map[i] != NULL; i++)
        for (int j = 1; w->map[i][j].height != -100; j++)
            if (cmp_color(sfConvexShape_getOutlineColor(w->map[i-1]\
[j-1].shape), sfRed) == 1)
                sfRenderWindow_drawConvexShape(w->window, w->map[i-1]\
[j-1].shape, NULL);
}

void my_world(world_t *w, int *type)
{
    page_t p = w->page[1];
    static int a = 0;

    sfRenderWindow_drawSprite(w->window, p.background, NULL);
    print_map(w);
    if (passed_text(w, p.text[0]) == 1) {
        sfMusic_play(w->music[1]);
        *type = 0;
    }
    for (int i = 0; i != 13; i++) {
        if (passed_button(w, p.rbutton[i]) == 1) {
            sfRectangleShape_setOutlineColor(p.rbutton[i], sfRed);
            a = 1 - 2*i;
        }
        sfRenderWindow_drawRectangleShape(w->window, p.rbutton[i], NULL);
    }
    move_map(w, &a);
    sfRenderWindow_drawText(w->window, p.text[0], NULL);
    sfRenderWindow_display(w->window);
    sfRenderWindow_clear(w->window, sfWhite);
}

int check_h(char **av)
{
    int i = 0;
    char *str = "-h\0";
    for (; av[1][i] != '\0'; i++)
        if (av[1][i] != str[i])return 1;
    write(1, "Map editor created with CSFML.\n\nUSAGE\n    ", 46);
    write(1, "./my_world (map)\n\nOPTIONS\n    -h    ", 39);
    write(1, "print the usage and quit.\n\nUSER INTERACTIONS\n    ", 52);
    write(1, "ECHAP    quit.\n    BY CLICKING    can change texture ", 54);
    write(1, "and height of the map\n", 22);
    return 0;
}

int main(int n, char **arg)
{
    if (n < 2) {
        write(1, "No map in arg\n", 14);
        return 84;
    }
    if (check_h(arg) == 0)return 0;
    world_t *w = create_map(arg[1]);
    if (w == NULL)return 84;
    void (*funct[2])(world_t *, int *) = {menu, my_world};

    if (n != 2 || w == NULL) return (84);
    for (int i = 0; sfRenderWindow_isOpen(w->window);) {
        if (i >= 0)(*funct[i])(w, &i);
        condition(w, i);
    }
    destroy(w);
}
