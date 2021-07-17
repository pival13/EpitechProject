/*
** EPITECH PROJECT, 2020
** doublebtree_get
** File description:
** get functions for doublebtree
*/

#include "double_btree.h"
#include <stdlib.h>

unsigned int double_btree_get_size(double_btree_t tree)
{
    if (tree == NULL)
        return 0;
    return 1 + double_btree_get_size(tree->right) + \
double_btree_get_size(tree->left);
}

unsigned int double_btree_get_depth(double_btree_t tree)
{
    int right;
    int left;

    if (tree == NULL)
        return 0;
    right = double_btree_get_depth(tree->right);
    left = double_btree_get_depth(tree->left);
    return 1 + (right > left ? right : left);
}

double double_btree_get_max_value(double_btree_t tree)
{
    double max;
    double tmp;

    if (tree == NULL)
        return 0;
    max = tree->value;
    if (tree->right != NULL) {
        tmp = double_btree_get_max_value(tree->right);
        if (tmp > max)
            max = tmp;
    }
    if (tree->left != NULL) {
        tmp = double_btree_get_max_value(tree->left);
        if (tmp > max)
            max = tmp;
    }
    return max;
}

double double_btree_get_min_value(double_btree_t tree)
{
    double min;
    double tmp;

    if (tree == NULL)
        return 0;
    min = tree->value;
    if (tree->right != NULL) {
        tmp = double_btree_get_min_value(tree->right);
        if (tmp < min)
            min = tmp;
    }
    if (tree->left != NULL) {
        tmp = double_btree_get_min_value(tree->left);
        if (tmp < min)
            min = tmp;
    }
    return min;
}
