/*
** EPITECH PROJECT, 2018
** main sokoban
** File description:
** main of sokoban
*/

int sokoban(char *arg, int nb_j);

int main(int n, char **arg)
{
    if (n != 2)
        return (84);
    sokoban(arg[1], 2);
}
