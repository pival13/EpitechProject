/*
** EPITECH PROJECT, 2018
** bonus2
** File description:
** next of bonus
*/

#include "my.h"
#include "sokoban.h"
#include <ncurses.h>
#include <stdlib.h>

int easy(void)
{
    int i = 0;
    int j = 6;
    char *str[12] = {SENT_EASY};

    while (i != 10) {
        bad_size(my_strlen(str[10])+10);
        print(str);
        mvprintw(LINES/2+j-1, COLS/2-5-my_strlen(str[4+j])/2, "==>");
        refresh();
        i = getch();
        (i == KEY_UP) ? (j--) : (j);
        (i == KEY_DOWN) ? (j++) : (j);
        (j < 0) ? (j = (j+7) % 7) : (j %= 7);
    }
    (j == 0) ? (endwin(), sokoban("bonus/map/map0.txt", 1)) : (0);
    (j == 1) ? (endwin(), sokoban("bonus/map/map2.txt", 1)) : (0);
    (j == 2) ? (endwin(), sokoban("bonus/map/map3.txt", 1)) : (0);
    (j == 3) ? (endwin(), sokoban("bonus/map/map1.txt", 1)) : (0);
    (j == 4) ? (endwin(), sokoban("bonus/map/map8.txt", 1)) : (0);
    (j == 5) ? (endwin(), sokoban("bonus/map/map9.txt", 1)) : (main_page());
}

int hard(void)
{
    int i = 0;
    int j = 0;
    char *str[12] = {SENT_HARD};

    while (i != 10) {
        bad_size(my_strlen(str[1]));
        print(str);
        mvprintw(LINES/2+j-1, COLS/2-5-my_strlen(str[4+j])/2, "==>");
        refresh();
        i = getch();
        (i == KEY_UP) ? (j--) : (j);
        (i == KEY_DOWN) ? (j++) : (j);
        (j < 0) ? (j = (j+5)%5) : (j %= 5);
        (i == 263) ? (draw_sentence()) : (0);
    }
    (j == 0) ? (endwin(), sokoban("bonus/map/map4.txt", 1)) : (0);
    (j == 1) ? (endwin(), sokoban("bonus/map/map10.txt", 1)) : (0);
    (j == 2) ? (endwin(), sokoban("bonus/map/map5.txt", 1)) : (0);
    (j == 3) ? (endwin(), sokoban("bonus/map/map7.txt", 1)) : (0);
    (j == 4) ? (endwin(), sokoban("bonus/map/map6.txt", 1)) : 0;
}

int impossible(void)
{
    int i = 0;
    int j = 3;
    char *str[12] = {SENT_IMPO};

    while (i != 10) {
        bad_size(my_strlen(str[1]));
        print(str);
        mvprintw(LINES/2+j-1, COLS/2-5-my_strlen(str[4+j])/2, "==>");
        refresh();
        i = getch();
        (i == KEY_UP) ? (j--) : (j);
        (i == KEY_DOWN) ? (j++) : (j);
        (j < 0) ? (j = (j+4)%4) : (j %= 4);
    }
    (j == 0) ? (endwin(), sokoban("bonus/map/map7_1.txt", 1)) : (0);
    (j == 1) ? (endwin(), sokoban("bonus/map/map6_1.txt", 1)) : (0);
    (j == 2) ? (endwin(), sokoban("bonus/map/map10_1.txt", 1)) : (0);
    (j == 3) ? (main_page()) : (0);
}

int mult(void)
{
    int i = 0;
    int j = 5;
    char *str[12] = {SENT_MULT};

    while (i != 10) {
        bad_size(my_strlen(str[0]));
        print(str);
        mvprintw(LINES/2+j-1, COLS/2-5-my_strlen(str[4+j])/2, "==>");
        refresh;
        i = getch();
        (i == KEY_UP) ? (j--) : j;
        (i == KEY_DOWN) ? (j++) : (j);
        (j < 0) ? (j = (j+6)%6) : (j %= 6);
    }
    (j == 0) ? (endwin(), sokoban("bonus/map/multi/map4.txt", 2)) : 0;
    (j == 1) ? (endwin(), sokoban("bonus/map/multi/map10.txt", 2)) : 0;
    (j == 2) ? (endwin(), sokoban("bonus/map/multi/map5.txt", 2)) : 0;
    (j == 3) ? (endwin(), sokoban("bonus/map/multi/map7.txt", 2)) : 0;
    (j == 4) ? (endwin(), sokoban("bonus/map/multi/map6.txt", 2)) : 0;
    (j == 5) ? (main_page()) : 0;
}

int main_page(void)
{
    int i = 0;
    int j = 0;
    char *str[12] = {SENT_MAIN};

    while (i != 10) {
        bad_size(my_strlen(str[8])+9);
        print(str);
        mvprintw(LINES/2+j, COLS/2-5-my_strlen(str[8])/2, "==>");
        refresh();
        i = getch();
        (i == KEY_UP) ? (j--) : (j);
        (i == KEY_DOWN) ? (j++) : (j);
        (j < 0) ? (j = (j+5)%5) : (j %= 5);
    }
    (j == 0) ? (easy()) : (0);
    (j == 1) ? (hard()) : (0);
    (j == 2) ? (impossible()) : (0);
    (j == 3) ? (mult()) : (attroff(COLOR_PAIR(1)), endwin(), exit(0));
}
