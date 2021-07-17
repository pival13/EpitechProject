/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** max_in_teams
*/

/**
* @brief Return an id for new client.
*
* @return unsigned long int
*/

unsigned long int max_in_team(void)
{
    static unsigned long int max = 0;
    ++max;
    return max;
}