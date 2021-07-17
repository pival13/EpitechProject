/*
** EPITECH PROJECT, 2019
** create_cs_struct.c
** File description:
** create cs struct
*/

#include "my.h"

void set_class_names_cs(c_save_t *cs, sfClock *cl, sfTexture **te)
{
    cs->class[0] = "Mage";
    cs->class[1] = "Summoner";
    cs->class[2] = "";
    cs->class[3] = "Berserker";
    cs->class[4] = "";
    cs->class[5] = "";
    cs->class[6] = "Archer";
    cs->class[7] = "Mage";
    cs->class[8] = "";
    cs->class[9] = "Archer";
    cs->class[10] = "Spearman";
    cs->class[11] = "Thief";
    cs->class[12] = "Ogre";
    cs->class[13] = "";
    cs->class[14] = "";
    cs->created = create_obj_t_sprite
    (cl, NULL, te[CREATED_CS]);
    sprite_set_scale(cs->created->sprite, 2, 2);
    cs->created->time_anim->seconds = 5;
    sprite_set_position(cs->created->sprite, 1920 / 2, 1080 / 2);
}

c_save_t *create_cs_struct(sfClock *cl, sfTexture **te, sfFont *f, sfFont *f2)
{
    c_save_t *cs = malloc(sizeof(c_save_t));
    sfVector2f pos = {580, 560};

    cs->panel = create_obj_t_sprite
    (cl, NULL, te[PANEL_CS]);
    cs->panel->origin.x = 0;
    cs->panel->origin.y = 0;
    sfSprite_setOrigin(cs->panel->sprite, cs->panel->origin);
    cs->character = sfSprite_create();
    sprite_set_scale(cs->character, 1.3, 1.3);
    sprite_set_position(cs->character, 1150, 470);
    for (int i = 0; i < 10; i++)
        cs->t[i] = create_text("", (i >= 7 && i <= 9) ?
        (30) : (40), (i != 4) ? (f2) : (f));
    cs->text_gte = create_text("Enter a name ...", 30, f2);
    sfText_setPosition(cs->text_gte, pos);
    set_class_names_cs(cs, cl, te);
    return (cs);
}

void destroy_cs_struct(c_save_t *cs)
{
    for (int i = 0; i < 10; i++)
        sfText_destroy(cs->t[i]);
    sfSprite_destroy(cs->character);
    destroy_obj_t(cs->panel);
    destroy_obj_t(cs->created);
    free(cs);
}
