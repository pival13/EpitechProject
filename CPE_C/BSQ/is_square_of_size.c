/*
** EPITECH PROJECT, 2018
** is_square_of_size
** File description:
** return if there is a square on this place
*/

int is_square_of_size(char **map, int row, int col, int square_size)
{
    int i = 0;
    int j = 0;

    if (map[row][col] != '.')
        return (0);
    while (i != square_size) {
        while (j != square_size && map[row+i][col+j] == '.')
            j++;
        if (map[row+i][col+j] != '.' && j < square_size)
            return (0);
        i++;
        j = 0;
    }
    return (1);
}
