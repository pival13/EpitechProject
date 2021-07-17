/*
** EPITECH PROJECT, 2019
** set_volume.c
** File description:
** set volume
*/

#include "my.h"

void set_volume(rpg_t *w)
{
    for (int i = 0; w->sounds[i] != NULL; i++) {
        sfMusic_setVolume(w->sounds[i], w->sett->sound_volume);
    }
    for (int i = 0; w->musics[i] != NULL; i++) {
        sfMusic_setVolume(w->musics[i], w->sett->music_volume);
    }
}
