/*
** EPITECH PROJECT, 2020
** main
** File description:
** main of ex00
*/

#include <iostream>
#include <fstream>

int main(int n, char **arg)
{
    std::ifstream f;
    std::string s;

    if (n == 1)
        std::cerr << "my_cat: Usage: ./my_cat file [...]" << std::endl;
    for (int i = 1; i != n; i++) {
        f.open(arg[i], std::ifstream::in);
        if (!f.is_open())
            std::cerr << "my_cat: " << arg[i] << ": No such file or directory" << std::endl;
        else {
            //while (!f.eof()) {
                std::getline(f, s, '\0');
                std::cout << s;// << std::endl;
            //}
        }
        f.close();
    }
}