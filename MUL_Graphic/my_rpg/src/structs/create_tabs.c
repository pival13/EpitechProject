/*
** EPITECH PROJECT, 2019
** create_tabs.c
** File description:
** create tabs
*/

#include "my.h"

int create_texture_tab(rpg_t *w)
{
    char **cnt = read_file("./data/textures.data");
    int size = nb_row(cnt);

    w->textures = NULL;
    if (my_arraylen(cnt) != TEXTURES_SIZE) {
        my_dprintf(2, "textures.data is bugged or missing.\n");
        return (84);
    }
    w->textures = malloc(sizeof(sfTexture *) * (TEXTURES_SIZE + 1));
    for (int i = 0; i < size; i++)
        w->textures[i] = NULL;
    for (int i = 0; cnt[i] != NULL; i++) {
        w->textures[i] = sfTexture_createFromFile(cnt[i], NULL);
        if (w->textures[i] == NULL) {
            my_dprintf(2, "A texture file has a problem.\n");
            return (84);
        }
        w->textures[i+1] = NULL;
    }
    return (0);
}

int create_sounds_and_musics_tab_malloc(rpg_t *w, char **cnt1, char **cnt2)
{
    w->sounds = malloc(sizeof(sfMusic *) * (nb_row(cnt1) + 1));
    w->musics = malloc(sizeof(sfMusic *) * (nb_row(cnt2) + 1));
    w->sounds[0] = NULL;
    w->musics[0] = NULL;
    for (int i = 0; cnt1[i] != NULL; i++) {
        w->sounds[i] = sfMusic_createFromFile(cnt1[i]);
        if (w->sounds[i] == NULL) {
            my_dprintf(2, "A sound file has a problem.\n");
            return (84);
        }
        w->sounds[i+1] = NULL;
    }
    return (0);
}

int create_sounds_and_musics_tab(rpg_t *w)
{
    char **cnt1 = read_file("./data/sounds.data");
    char **cnt2 = read_file("./data/musics.data");

    if (my_arraylen(cnt1) != S_SIZE || my_arraylen(cnt2) != M_SIZE) {
        my_dprintf(2, "sounds.data/musics.data is/are bugged or missing.\n");
        return (84);
    }
    if (create_sounds_and_musics_tab_malloc(w, cnt1, cnt2) == 84)
        return (84);
    for (int i = 0; cnt2[i] != NULL; i++) {
        w->musics[i] = sfMusic_createFromFile(cnt2[i]);
        if (w->musics[i] == NULL) {
            my_dprintf(2, "A music file has a problem.\n");
            return (84);
        }
        sfMusic_setLoop(w->musics[i], sfTrue);
        w->musics[i+1] = NULL;
    }
    return (0);
}
