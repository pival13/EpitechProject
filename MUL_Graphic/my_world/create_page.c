/*
** EPITECH PROJECT, 2019
** create_map
** File description:
** error gestion
*/

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include "my.h"
#include "my_world.h"

void move_rectangle(sfRectangleShape *rect, float x, float y)
{
    sfRectangleShape_setPosition(rect, (sfVector2f){x, y});
}

void create_menu(world_t *w)
{
    page_t p = w->page[0];

    p.text = malloc(sizeof(sfText *) * 5);
    p.text[0] = create_text("Worlderful", 50, w->font);
    p.text[1] = create_text("That's working!", 50, w->font);
    p.text[2] = create_text("Play", 72, w->font);
    p.text[3] = create_text("Quit", 72, w->font);
    p.text[4] = NULL;
    move_text(p.text[0], SIZE(x)/2, 100);
    move_text(p.text[1], SIZE(x)/2, 150);
    move_text(p.text[2], SIZE(x)/2, 350);
    move_text(p.text[3], SIZE(x)/2, 450);
    color_text(p.text[0], sfBlack);
    color_text(p.text[1], sfBlack);
    color_text(p.text[2], sfBlack);
    color_text(p.text[3], sfBlack);
    w->page[0] = p;
}

void create_button_editpage(page_t *p, world_t *w)
{
    sfVector2f pos[7] = {{550, 10}, {595, 120}, {720, 70}, {685, 80}, {6\
70, 110}, {675, 65}, {716, 115}};
    float angle[7] = {0, 180, 180, 0, 0, 90, 270};
    for (int i = 0; i != 7; ++i) {
        p->rbutton[i] = sfRectangleShape_create();
        sfRectangleShape_setTexture(p->rbutton[i], p->tbutton[i], sfTrue);
        sfRectangleShape_setSize(p->rbutton[i], (sfVector2f){50, 50});
        sfRectangleShape_setPosition(p->rbutton[i], pos[i]);
        sfRectangleShape_setOutlineThickness(p->rbutton[i], 1.5);
        sfRectangleShape_rotate(p->rbutton[i], angle[i]);
    }
    sfRectangleShape_setSize(p->rbutton[3], (sfVector2f){20, 20});
    for (int i = 7; i != 13; i++) {
        p->rbutton[i] = sfRectangleShape_create();
        sfRectangleShape_setTexture(p->rbutton[i], w->texture[i - 7], sfTrue);
        sfRectangleShape_setSize(p->rbutton[i], (sfVector2f){50, 50});
        sfRectangleShape_setPosition(p->rbutton[i], (sfVector2f){160+60*\
(i-7), 40});
        sfRectangleShape_setOutlineThickness(p->rbutton[i], 1.5);
    }
}

void create_editpage(world_t *w)
{
    page_t p = w->page[1];
    char *image_button[7] = {"sprite/modify_up.png", \
    "sprite/modify_up.png", "sprite/down_button.png", \
    "sprite/circle_button.png", "sprite/down_button.png", \
    "sprite/down_button.png", "sprite/down_button.png"};

    for (int i = 0; i != 7; ++i)
        p.tbutton[i] = sfTexture_createFromFile(image_button[i], NULL);
    p.text = malloc(sizeof(sfText *) * 2);
    p.text[0] = create_text("Back", 50, w->font);
    p.text[1] = NULL;
    move_text(p.text[0], 60, 50);
    color_text(p.text[0], sfBlack);
    create_button_editpage(&p, w);
    w->page[1] = p;
}

void create_page(world_t *w)
{
    w->page = malloc(sizeof(page_t) * 2);
    w->page[0].tbackground = sfTexture_createFromFile("sprite/menu_my_world.\
png", NULL);
    w->page[1].tbackground = sfTexture_createFromFile("sprite/main_background\
.png", NULL);
    for (int i = 0; i != 2; i++) {
        w->page[i].background = sfSprite_create();
        sfSprite_setTexture(w->page[i].background, w->page[i].tbackground, sf\
True);
    }
    create_menu(w);
    create_editpage(w);
}
