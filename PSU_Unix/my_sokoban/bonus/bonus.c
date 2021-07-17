/*
** EPITECH PROJECT, 2018
** bonus
** File description:
** bonus of sokoban
*/

#include <sys/ioctl.h>
#include <ncurses.h>
#include "my.h"
#include <unistd.h>
#include <stdlib.h>

int sokoban(char *str, int nb_j);

int main_page(void);

int draw_sentence(void)
{
    char *str = "What??? You've found the exit? Impossible!!!";

    clear();
    mvprintw(LINES/2, COLS/2-my_strlen(str)/2, str);
    refresh();
    usleep(30 * 100000);
    main_page();
}

int bad_size(int width)
{
    while (COLS < width || LINES < 14) {
        clear();
        mvprintw(LINES/2, COLS/2-24, "What are you doing? Enlarge the \
windows! NOW!!!");
        refresh();
    }
}

void print(char *str[12])
{
    clear();
    mvprintw(LINES/2-7, COLS/2-my_strlen(str[0])/2, str[0]);
    mvprintw(LINES/2-5, COLS/2-my_strlen(str[1])/2, str[1]);
    mvprintw(LINES/2-4, COLS/2-my_strlen(str[2])/2, str[2]);
    mvprintw(LINES/2-3, COLS/2-my_strlen(str[3])/2, str[3]);
    mvprintw(LINES/2-1, COLS/2-my_strlen(str[4])/2, str[4]);
    mvprintw(LINES/2, COLS/2-my_strlen(str[5])/2, str[5]);
    mvprintw(LINES/2+1, COLS/2-my_strlen(str[6])/2, str[6]);
    mvprintw(LINES/2+2, COLS/2-my_strlen(str[7])/2, str[7]);
    mvprintw(LINES/2+3, COLS/2-my_strlen(str[8])/2, str[8]);
    mvprintw(LINES/2+4, COLS/2-my_strlen(str[9])/2, str[9]);
    mvprintw(LINES/2+5, COLS/2-my_strlen(str[10])/2, str[10]);
    mvprintw(LINES/2+6, COLS/2-my_strlen(str[11])/2, str[11]);
}

int main(void)
{
    initscr();
    keypad(stdscr, true);
    curs_set(false);
    start_color();
    init_pair(1, 15, 0);
    attron(COLOR_PAIR(1));
    main_page();
}
