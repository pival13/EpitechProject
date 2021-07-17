/*
** EPITECH PROJECT, 2019
** obj.c
** File description:
** create obj_t
*/

#include "my.h"

obj_t *create_obj_t_sprite(sfClock *clock, char *sprite, sfTexture *texture)
{
    obj_t *obj = malloc(sizeof(obj_t));

    obj_init(obj);
    obj->sprite = sfSprite_create();
    obj->texture = texture;
    if (texture == NULL)
        obj->texture = sfTexture_createFromFile(sprite, NULL);
    sfSprite_setTexture(obj->sprite, obj->texture, sfFalse);
    obj->rect = sfSprite_getTextureRect(obj->sprite);
    obj->origin.x = obj->rect.width / 2;
    obj->origin.y = obj->rect.height / 2;
    sfSprite_setOrigin(obj->sprite, obj->origin);
    obj->pos.x = 0;
    obj->pos.y = 0;
    sfSprite_setPosition(obj->sprite, obj->pos);
    obj->scale = sfSprite_getScale(obj->sprite);
    obj->time_move = create_time_obj(clock);
    obj->time_anim = create_time_obj(clock);
    obj->anim_mode = 0;
    return (obj);
}

obj_t *create_obj_t_text(sfClock *clock, char *text, char *font_path)
{
    obj_t *obj = malloc(sizeof(obj_t));

    obj_init(obj);
    obj->chsize = 16;
    obj->content = my_strcpy(text);
    obj->font = sfFont_createFromFile(font_path);
    obj->text = sfText_create();
    obj->pos.x = 0;
    obj->pos.y = 0;
    sfText_setCharacterSize(obj->text, obj->chsize);
    sfText_setFont(obj->text, obj->font);
    sfText_setPosition(obj->text, obj->pos);
    sfText_setString(obj->text, text);
    obj->time_move = create_time_obj(clock);
    obj->time_anim = create_time_obj(clock);
    obj->anim_mode = 0;
    return (obj);
}

obj_t *create_obj_t_sound(sfClock *clock, char *sound_path)
{
    obj_t *obj = malloc(sizeof(obj_t));

    obj_init(obj);
    obj->sound = sfSound_create();
    obj->buffer = sfSoundBuffer_createFromFile(sound_path);
    sfSound_setBuffer(obj->sound, obj->buffer);
    obj->time_move = create_time_obj(clock);
    return (obj);
}

obj_t *create_obj_t_music(sfClock *clock, char *sound_path)
{
    obj_t *obj = malloc(sizeof(obj_t));

    obj_init(obj);
    obj->music = sfMusic_createFromFile(sound_path);
    obj->time_move = create_time_obj(clock);
    return (obj);
}

void destroy_obj_t(obj_t *obj)
{
    (obj->content != NULL) ? (free(obj->content)) : (0);
    (obj->text != NULL) ? (sfText_destroy(obj->text)) : (0);
    (obj->font != NULL) ? (sfFont_destroy(obj->font)) : (0);
    if (obj->sound != NULL)
        (sfSound_getStatus(obj->sound) != sfStopped) ?
        (sfSound_stop(obj->sound)) : (0);
    (obj->sound != NULL) ? (sfSound_destroy(obj->sound)) : (0);
    (obj->buffer != NULL) ? (sfSoundBuffer_destroy(obj->buffer)) : (0);
    if (obj->music != NULL)
        (sfMusic_getStatus(obj->music) != sfStopped) ?
        (sfMusic_stop(obj->music)) : (0);
    (obj->music != NULL) ? (sfMusic_destroy(obj->music)) : (0);
    (obj->sprite != NULL) ? (sfSprite_destroy(obj->sprite)) : (0);
    (obj->time_move != NULL) ? (destroy_time_obj(obj->time_move)) : (0);
    (obj->time_anim != NULL) ? (destroy_time_obj(obj->time_anim)) : (0);
    free(obj);
}
