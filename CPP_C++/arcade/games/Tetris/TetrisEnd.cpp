/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019 [WSL: Ubuntu]
** File description:
** PacmanEnd
*/
//10 x 22

#include "Tetris.hpp"

void Tetris::drawError()
{
    static msec t(0);
    static const std::string arr[] = {"%%%%% %   % %%%%% %%%%% %%%%  %   %  %%%  %    ",
                                      "  %   %%  %   %   %     %   % %%  % %   % %    ",
                                      "  %   % % %   %   %%%   %%%%  % % % %%%%% %    ",
                                      "  %   %  %%   %   %     %  %  %  %% %   % %    ",
                                      "%%%%% %   %   %   %%%%% %   % %   % %   % %%%%%",
                                      "                                               ",
                                      "         %%%%% %%%%  %%%%   %%%  %%%%          ",
                                      "         %     %   % %   % %   % %   %         ",
                                      "         %%%   %%%%  %%%%  %   % %%%%          ",
                                      "         %     %  %  %  %  %   % %  %          ",
                                      "         %%%%% %   % %   %  %%%  %   %         "};
    size_t x = getMapWidth()/2 - arr[0].length()/2;
    size_t y = getMapHeight()/2 - 5;

    cleanMap();
    if (t < now - msec(1000))
        t = now;
    else if (t < now - msec(500))
        for (size_t i = 0; i != 11; i++)
            for (size_t j = 0; j != arr[i].size(); j++)
                setMapAt(x+j, y+i, arr[i][j]);
}

void Tetris::errorPage()
{
    drawError();

    if (isKeyBack() || isKeyDown() || isKeyEnter() || isKeyLeft() || isKeyRight() || isKeyUp())
        backToMenu();
}

void Tetris::drawGameOver()
{
    static const std::string arr[] = {" %%%   %%%  %% %% %%%%%",
                                      "%     %   % % % % %    ",
                                      "%  %% %%%%% % % % %%%  ",
                                      "%   % %   % %   % %    ",
                                      " %%%  %   % %   % %%%%%",
                                      "                       ",
                                      " %%%  %   % %%%%% %%%% ",
                                      "%   % %   % %     %   %",
                                      "%   % %   % %%%   %%%% ",
                                      "%   %  % %  %     %  % ",
                                      " %%%    %   %%%%% %   %" };
    size_t x = getMapWidth()/2 - 11;
    size_t y = getMapHeight()/2 - 5;

    for (size_t i = 0; i != 11; i++)
        for (size_t j = 0; j != arr[i].size(); j++)
            if (arr[i][j] != ' ')
                setMapAt(x+j, y+i, arr[i][j]);
}

void Tetris::gameOverPage()
{
    drawGameOver();

    if (isKeyBack() || isKeyDown() || isKeyEnter() || isKeyLeft() || isKeyRight() || isKeyUp())
        backToMenu();
}
