/*
** EPITECH PROJECT, 2020
** tree
** File description:
** tree
*/

#include "tree_traversal.h"
#include <stdlib.h>

bool tree_is_empty(tree_t tree)
{
    return tree == NULL;
}

void tree_node_dump(tree_node_t *tree_node, dump_func_t dump_func)
{
    if (tree_node == NULL)
        return;
    dump_func(tree_node->data);
}

bool init_tree(tree_t *tree_ptr, void *data)
{
    tree_t ptr = malloc(sizeof(tree_node_t));

    if (ptr == NULL)
        return false;
    ptr->data = data;
    ptr->parent = NULL;
    ptr->children = NULL;
    *tree_ptr = ptr;
    return true;
}

tree_node_t *tree_add_child(tree_node_t *tree_node, void *data)
{
    tree_node_t *node;

    if (tree_node == NULL)
        return NULL;
    if (init_tree(&node, data) == false)
        return NULL;
    node->parent = tree_node;
    list_add_elem_at_back(&tree_node->children, node);
    return node;
}

bool tree_destroy(tree_t *tree_ptr)
{
    list_t tmp;
    tree_t node;

    if (*tree_ptr == NULL)
        return false;
    while ((*tree_ptr)->children != NULL) {
        tmp = (*tree_ptr)->children->next;
        node = (*tree_ptr)->children->value;
        tree_destroy(&node);
        free((*tree_ptr)->children);
        (*tree_ptr)->children = tmp;
    }
    free(*tree_ptr);
    *tree_ptr = NULL;
    return true;
}