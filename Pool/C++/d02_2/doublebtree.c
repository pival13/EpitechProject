/*
** EPITECH PROJECT, 2020
** doublebtree
** File description:
** double Btree
*/

#include "double_btree.h"
#include <stdlib.h>
#include <stdbool.h>

bool double_btree_is_empty(double_btree_t tree)
{
    return tree == NULL;
}

bool double_btree_create_node(double_btree_t *root_ptr, double value)
{
    double_btree_t ptr = malloc(sizeof(doublebtree_node_t));

    if (ptr == NULL)
        return false;
    ptr->value = value;
    ptr->left = NULL;
    ptr->right = NULL;
    *root_ptr = ptr;
    return true;
}

bool double_btree_delete(double_btree_t *root_ptr)
{
    if (*root_ptr == NULL)
        return false;
    double_btree_delete(&(*root_ptr)->right);
    double_btree_delete(&(*root_ptr)->left);
    free(*root_ptr);
    *root_ptr = NULL;
    return true;
}