/*
** EPITECH PROJECT, 2019
** enum.h
** File description:
** enum header
*/

#ifndef ENUM_H
#define ENUM_H

typedef enum key_mode {
    M_MODE,
    K_MODE
} key_mode;

typedef enum page_id_s {
    MENU,
    CH,
    MAP,
    SETT,
    SAVE,
    QM,
    FIGHT,
    INTRO
} page_id_t;

typedef enum buttons_main_menu_s {
    PLAY,
    SETTINGS,
    QUIT
} buttons_main_menu_t;

typedef enum buttons_ingame_menu_s {
    INVENTORY,
    QUEST,
    SAVE_IG,
    SETTINGS_IG,
    QUIT_IG
} buttons_ingame_menu_t;

typedef enum textures_id {
    BGDMM,
    PLAYMM,
    SETTMM,
    QUITMM,
    LOADMM,
    CREATEMM,
    DELETEMM,
    RETURNMM,
    MUSICSETT,
    SNDFXSETT,
    BARSSETT,
    MAR,
    DEMONF,
    DEMONFMAG,
    DEMONFINV,
    DEMONH,
    DEMONHMAG,
    DEMONHINV,
    NAINF,
    NAINFHAC,
    NAINH,
    NAINHHAC,
    ELFF,
    ELFFARC,
    ELFFMAG,
    ELFH,
    ELFHARC,
    ELFHMAG,
    HUMANF,
    HUMANFARC,
    HUMANFLAN,
    HUMANFDAG,
    HUMANH,
    HUMANHARC,
    HUMANHLAN,
    HUMANHDAG,
    OGREF,
    OGREFF,
    OGREH,
    OGREHH,
    TITLEMM,
    DORA,
    CHOCO,
    DIO,
    ET,
    FREEZER,
    PACMAN,
    ZELDA,
    BIRD,
    MARIO,
    FOAM,
    MURLOC,
    POKEMON,
    PONG,
    OCTOPUS,
    RAYMAN,
    ASTERIX,
    SHAGGY,
    MUTANT,
    TETRIS,
    CITY,
    DEMON,
    FOREST,
    HOLY_FOREST,
    MOUNTAIN,
    PLAIN,
    TEMPLE,
    SWAMP,
    PANEL_IG,
    CH_IG,
    QUESTS_B_IG,
    SAV_IG,
    SETT_IG,
    QUIT_B_IG,
    MESSAGE_SAVE_IG,
    BUP_QM,
    BLEFT_QM,
    BRIGHT_QM,
    BDOWN_QM,
    TITLE_QM,
    TITLE_CH,
    BGD_CH,
    BGD_QM,
    RETURN2,
    DIAMOND,
    PANEL_CS,
    BASE,
    DELETEDMM,
    NOSAVEMM,
    CREATED_CS,
    ARROW_INT,
    CHOICE_INT,
    DBOX_INT,
    NARR_INT,
    BGD_INT,
    DEMON_IG,
    DWARF_IG,
    ELF_IG,
    HUMAN_IG,
    OGRE_IG,
    NOMANA,
    FUITE,
    TCITY,
    TDEMON,
    TMOUNTAIN,
    TFOREST,
    NOMONEY,
    BOUGHT,
    TEXTURES_SIZE
} textures_id;

typedef enum musics_id {
    MUSIC_MENU,
    MUSIC_WORLD,
    MUSIC_FIGHT,
    M_SIZE
} musics_id;

typedef enum sounds_id {
    S_INTERACTION,
    S_FIGHT,
    S_PAGE,
    S_SIZE
} sounds_id;

#endif
