/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** handle_command
*/

#include "server.h"

/**
* @brief Delete useless part of pending command.
*
* @param tmp Current client.
*/
static void delete_useless_part(client_t *tmp)
{
    size_t i = 0;
    bool begin = false;
    char *str_tmp = malloc(sizeof(char) * (strlen(tmp->pending_command) + 1));

    memset(str_tmp, 0, strlen(tmp->pending_command) + 1);
    for (size_t j = 0; tmp->pending_command[j]; ++j) {
        if (tmp->pending_command[j] == '\n' && begin == false)
            begin = true;
        else if (begin == true) {
            str_tmp[i] = tmp->pending_command[j];
            ++i;
        }
    }
    free(tmp->pending_command);
    tmp->pending_command = strdup(str_tmp);
    free(str_tmp);
}

/**
* @brief Parse the command to extract one command at a time.
*
* @param tmp Current client.
*/
static void bring_command(client_t *tmp)
{
    char **array = NULL;

    if (found_separator(tmp->pending_command, '\n') == false)
        return;
    array = str_to_word_array(tmp->pending_command, "\n");
    if (array == NULL || array[0] == NULL)
        return;
    tmp->readbuffer = strdup(array[0]);
    if (array[1] != NULL) {
        delete_useless_part(tmp);
    } else {
        free(tmp->pending_command);
        tmp->pending_command = NULL;
    }
    if (tmp->readbuffer == NULL)
        send_client(tmp, "ko\n");
    free_array(array);
}

static bool string_is_space(char *str)
{
    for (size_t i = 0; str[i] != '\0'; ++i)
        if (str[i] != ' ')
            return false;
    return true;
}

/**
 * @brief Check if the command is good.
 *
 * @param tmp Current client.
 * @return true
 * @return false
 */
static int check_command(client_t *tmp)
{
    if (tmp->readbuffer == NULL && tmp->pending_command == NULL)
        return 1;
    if (tmp->pending_command == NULL && is_equal("\n", tmp->readbuffer) \
== true) {
        free(tmp->readbuffer);
        tmp->readbuffer = NULL;
        return 1;
    }
    if (tmp->readbuffer != NULL) {
        if (my_strlen(tmp->pending_command) + strlen(tmp->readbuffer) > \
LIMIT_BUFFER) {
            tmp->is_free = true;
            return EXIT_FAILURE;
        }
        if (string_is_space(tmp->readbuffer) == true)
            return EXIT_FAILURE;
        my_strcat(&tmp->pending_command, tmp->readbuffer);
    }
    return EXIT_SUCCESS;
}

/**
* @brief Merge the new command with the pending command.
*
* @param tmp Current client.
*/
void handle_command(client_t *tmp)
{
    int check = check_command(tmp);

    if (check == EXIT_FAILURE || check == 1) {
        check == EXIT_FAILURE ? my_strcat(&tmp->buffer, "ko") : 0;
        return;
    }
    free(tmp->readbuffer);
    tmp->readbuffer = NULL;
    bring_command(tmp);
}
