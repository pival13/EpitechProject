/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** main
*/

#include "server.h"

volatile int stop = 1;

/**
* @brief Function stop the server.
*
* @param handler sended signal.
*/
void signal_handler(__attribute__((unused)) int handler)
{
    stop = 0;
}

static int print_help(void)
{
    printf("USAGE: ./zappy_server -p port -x width -y height -n name1 name2 \
... -c clientsNb -f freq\n\
\tport\tis the port number\n\
\twidth\tis the width of the world\n\
\theight\tis the height of the world\n\
\tnameX\tis the name of the team X\n\
\tclientsNb\tis the number of authorized clients per team\n\
\tfreq\tis the reciprocal of time unit for execution of action\n\n\
-D basic parameters editable in the json file\n");
    return EXIT_SUCCESS;
}

static void display_information(server_t server)
{
    printf("Client number : %d\n", server.args.client_number);
    printf("Frequence : %d\n", server.args.freq);
    printf("Height : %d\n", server.args.height);
    printf("Width : %d\n", server.args.width);
    printf("Port : %d\n", server.args.port);
    for (int i = 0; server.args.name[i]; ++i)
        printf("Team name [%d] : %s\n", i, server.args.name[i]);
}

/**
* @brief Main funcion of the project.
*
* @param ac Number of paramaters.
* @param av Char ** array who contains all parameters.
* @return int
*/
int main(int ac, char **av)
{
    server_t server;
    signal(SIGINT, signal_handler);
    srand(time(NULL));

    if (ac == 2 && (strcmp(av[1], "-h") == 0 || strcmp(av[1], "--help") == 0))
        return print_help();
    if (handle_args(&server, av) == EXIT_FAILURE || \
init_server(&server) == EXIT_FAILURE || \
check_args(&server) == EXIT_FAILURE) {
        free_struct(&server);
        return EXIT_FAILURE;
    }
    display_information(server);
    init_map(&server);
    while (stop)
        server_loop(&server);
    free_struct(&server);
    return EXIT_SUCCESS;
}
