/*
** EPITECH PROJECT, 2019
** create_rpg_struct
** File description:
** create rpg struct
*/

#include "my.h"

int check_rpg_struct_errors(rpg_t *w)
{
    int error = 0;

    if (w->cs == NULL || w->intro == NULL || w->ingame == NULL ||
        w->fight == NULL) {
        error = 84;
    }
    if (w->win == NULL || w->font == NULL || w->font2 == NULL) {
        error = 84;
    } if (w->qm == NULL || w->sett == NULL || w->mm == NULL)
        error = 84;
    if (error == 84) {
        sfRenderWindow_destroy(w->win);
        for (int i = 0; w->musics != NULL && w->musics[i] != NULL; sfMusic_des\
troy(w->musics[i++]));
        for (int i = 0; w->sounds != NULL && w->sounds[i] != NULL; sfMusic_des\
troy(w->sounds[i++]));
        (w->sounds != NULL) ? (free(w->sounds)) : (0);
        (w->musics != NULL) ? (free(w->musics)) : (0);
    }
    return (error);
}

int create_rpg_struct3(rpg_t *w)
{
    int nb = 5;
    void *adress = &nb;
    long long long_seed = (long long)(adress);
    unsigned int res = long_seed;

    srand(res);
    w->sett->sound_volume = 40;
    w->sett->music_volume = 20;
    set_volume(w);
    for (int i = 0; i < 5; i++) {
        w->mob[i].stat.hp = 0;
        w->mob[i].stat.atk= 0;
        w->mob[i].stat.def = 0;
        w->mob[i].stat.res = 0;
        w->mob[i].stat.agi = 0;
    }
    sfRenderWindow_setFramerateLimit(w->win, 144);
    return (check_rpg_struct_errors(w));
}

int create_rpg_struct2(rpg_t *w)
{
    char *name = "Acheron's War";

    w->cursor = create_key_cursor(w->clock);
    mod_scale(w->cursor, 0.1);
    w->win = sfRenderWindow_create(w->mode, name,
    sfResize | sfClose | sfFullscreen, NULL);
    w->fight = create_fight_struct(w->clock);
    sprite_set_origin(w->cursor->sprite, 0, 0);
    w->font = sfFont_createFromFile("data/others/arial.ttf");
    w->font2 = sfFont_createFromFile("data/fonts/MedusaGothicD.ttf");
    if (create_map(w) == 84)
        return (84);
    w->event.type = 0;
    w->key_mode = M_MODE;
    w->ingame = create_ingame_menu_struct(w->clock, w->textures);
    for (int i = 0; i != 7; i++)
        w->pause_mode[i] = 0;
    w->cs = create_cs_struct(w->clock, w->textures, w->font, w->font2);
    w->intro = create_intro_struct(w->clock, w->textures);
    return (create_rpg_struct3(w));
}

rpg_t *create_rpg_struct(void)
{
    rpg_t *w = malloc(sizeof(rpg_t));

    w->mode = sfVideoMode_getDesktopMode();
    if (w == NULL)
        return (NULL);
    w->page = MENU;
    w->old_page = MENU;
    w->clock = sfClock_create();
    if (create_texture_tab(w) == 84)
        return (NULL);
    w->mm = create_main_menu_struct(w->clock, w->textures);
    w->sett = create_settings_struct(w->clock, w->textures);
    w->qm = create_quest_menu_struct(w->clock, w->textures);
    if (load_data(w) == 84 || read_quest(w) == 84
        || create_sounds_and_musics_tab(w) == 84 || create_rpg_struct2(w) == 84)
        return (NULL);
    w->ch = create_character_ingame(w->clock, w->textures);
    sfRenderWindow_setMouseCursorVisible(w->win, sfFalse);
    return (w);
}

int destroy_rpg_struct(rpg_t *w)
{
    sfRenderWindow_destroy(w->win);
    sfClock_destroy(w->clock);
    destroy_settings_struct(w->sett);
    destroy_main_menu_struct(w->mm);
    destroy_obj_t(w->cursor);
    destroy_ingame_menu_struct(w->ingame);
    destroy_character_texture(w->ch);
    destroy_quest_menu_struct(w->qm);
    for (int i = 0; w->textures[i] != NULL; i++)
        sfTexture_destroy(w->textures[i]);
    for (int i = 0; w->musics[i] != NULL; sfMusic_destroy(w->musics[i++]));
    for (int i = 0; w->sounds[i] != NULL; sfMusic_destroy(w->sounds[i++]));
    free(w->textures);
    free(w->sounds);
    free(w->musics);
    destroy_cs_struct(w->cs);
    destroy_intro_struct(w->intro);
    destroy_map(w->map);
    free(w);
    return (84);
}
