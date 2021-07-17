/*
** EPITECH PROJECT, 2019
** my.h
** File description:
** header
*/

#ifndef MY_H
#define MY_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int help_option(char **av);
double calcul_func(double x, double n);
double integration_midpoint(double (*funct)(double, double), double min, double max, double n);
double integration_trapez(double (*funct)(double, double), double min, double max, double n);
double integration_simpson(double (*funct)(double, double), double min, double max, double n);

#endif
