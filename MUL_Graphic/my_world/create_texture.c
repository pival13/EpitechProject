/*
** EPITECH PROJECT, 2019
** create texture
** File description:
** create texture
*/

#include "my_world.h"

void create_texture(world_t *w)
{
    char *file[7] = {"sprite/fond_bleu_a.png", "sprite/fond_bleu_\
b.png", "sprite/fond_bleu_c.png", "sprite/algue.png", "sprite/cor\
ail.png", "sprite/anemone.png", "sprite/round.png"};
    for (int i = 0; i != 7; ++i)
        w->texture[i] = sfTexture_createFromFile(file[i], NULL);
}
