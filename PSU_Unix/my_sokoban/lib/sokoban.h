/*
** EPITECH PROJECT, 2018
** sokoban.h
** File description:
** header of my_sokoban
*/

#define IF_BOX_IS_BLOCK if (map[i][j] == 'X' && ((map[i][j-1] == '#' && \
(map[i+1] == NULL || map[i+1][j] == '#')) || ((map[i+1] == NULL || map[i+1]\
[j] == '#') && map[i][j+1] == '#') || (map[i][j+1] == '#' && map[i-1][j] \
== '#') || (map[i][j-1] == '#' && map[i-1][j] == '#')))
#define CAN_MOVE_BOX(letter, cell, ncell) (i == letter && cell == 'X' && \
(ncell == ' ' || ncell == 'O'))
#define DRAW(letter, letter2, nb) (map[j][i] == letter) ? (attron(COLOR_PAIR\
(nb)), mvprintw(LINES/2 - pos[0]/2 + j, COLS/2 - pos[1]/2 + i, "%c", letter2), \
attroff(COLOR_PAIR(nb))) : (map[j][i]);
#define CHECK_CHAR (map[i][j] != 'P' && map[i][j] != 'O' && map[i][j] != \
'X' && map[i][j] != '#' && map[i][j] != ' ' && map[i][j] != '\n') ? exit \
(84) : map[i][j]
#define CHECK_CHAR_MULT (map[i][j] != 'P' && map[i][j] != 'O' && map[i][j] \
!= 'X' && map[i][j] != '#' && map[i][j] != ' ' && map[i][j] != '\n' && map[i]\
[j] != 'Q') ? exit (84) : map[i][j]
#define MOVE_DOWN(key, x, y, player) (x+1 < pos_o[0][0]-1 && i == key && \
(map[x+1][y] == ' ' || map[x+1][y] == 'O')) ? (map[x][y] = ' ', map[x+1]\
[y] = player) : 0
#define MOVE_UP(key, x, y, player) (x-1 > 0 && i == key && (map[x-1][y] == \
' ' || map[x-1][y] == 'O')) ? (map[x][y] = ' ', map[x-1][y] = player) : 0
#define MOVE_RIGHT(key, x, y, player) (y+1 < pos_o[0][1]-1 && i == key && \
(map[x][y+1] == ' ' || map[x][y+1] == 'O')) ? (map[x][y] = ' ', map[x]\
[y+1] = player) : 0
#define MOVE_LEFT(key, x, y, player) (y-1 > 0 && i == key && (map[x][y-1] \
== ' ' || map[x][y-1] == 'O')) ? (map[x][y] = ' ', map[x][y-1] = player) : 0
#define USAGE "USAGE\n\t./my_sokoban map\n\nDESCRIPTION\n\tmap\t\tfile repres\
enting the warehouse map, containing '#' for walls,\n\t\t\t'P' for player, 'X' \
for boxes and 'O' for storage locations.\n\nUSER INTERACTIONS\n\tARROW_KEYS\t\
move the player in the corresponding direction.\n\tR\t\tRestart the map.\n\t\
SPACE\t\tQuit the game.\n"
#define SENT_MAIN "Welcome to my Sokoban!!!", "How are you? Fine I hope.\
", "Well, we're not here to speak but to play, I think.", "Well, if a computer \
can think, and that's not very true for now. But, who know?", "So, there are \
several possiblities, make your choice:", "- The Easy mode. Well, that's \
... easy. Too easy.", "- The Hard mode. That's better. There is challenge, \
depression, madness, suicide... But you're different. I'm sure.", "- The \
Impossible mode. That is ... ... ... impossible. Even for me, the super mega \
giga ultra intelligent computer, so for you...", "- Here you can play with a \
friend. But as you don't have any friends, it will be hard. Oh, and I am not \
your friend, so I can't help you.","- Or you can quit if you are too impressed \
or too scared to play, but ... are you brave enough for that?", "", "Now, make \
your choice."
#define SENT_EASY "You've chosen Easy? Are you serious?", "Are you so stupid \
you can't even try the Hard?", "Or maybe the Hard is already too hard for you?\
", "Well, then chose an easy level:", "- Map 1", "- Map 2", "- Map 3", "- Map \
4", "- Map 5", "- Map 6", "Seriously, it's really too easy, change difficulty\
", ""
#define SENT_HARD "You've chosen Hard? Excellent choice!", "So, you can \
choose between the suicide, the depression or the madness.", "... That was \
just a joke, don't worry :D", "Well, then chose an hard level:", "- Map 1", "\
- Map 2", "- Map 3", "- Map 4", "- Map 5", "You can also change difficulty, \
but ...", "", ""
#define SENT_IMPO "You've chosen Impossible? Are you serious?!", "Have you \
really understand that even the super mega giga ultra supra computer that I \
am can't solve this?", "Or you think you're better than me, hum?", "Well, then \
chose an impossible level and cry:", "- Map 1", "- Map 2", "- Map 3", "You \
know that's to hard for you, change difficulty", "", "", "", ""
#define SENT_MULT "You've chosen Multiplayer? You have a friend O_o ???.", "\
I hope you haven't forced your 'friend'.", "Otherwise, I will have to give you \
my most impossible level.", "Well, then choose a frie... Eh a level:", "- Map \
1", "- Map 2", "- Map 3", "- Map 4", "- Map 5", "Your friend leave you, isn't \
it? So, chose an other difficulty.", "", ""

#ifndef _SOKOBAN_H_
#define _SOKOBAN_H_

char **load_2d_arr_from_file(char *path);
void check_map(char **map, int **pos_o);
void change_map(char **map, int i, int **pos_o, int nb_j);
void free_all(int **pos_o, char **map);
void check_size(int **pos_o, char **map);
int make_game(char **map, int **pos_o, int i, int nb_j);
void get_player(int *x, int *y, char **map, char player);
void draw_o(char **map, int **pos_o);
int sokoban(char *str, int nb_j);
int main_page(void);
int draw_sentence(void);
int bad_size(int width);
void print(char *str[12]);
void display_with_color(char **map, int *size);

#endif //_SOKOBAN_H_
