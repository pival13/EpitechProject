/*
** EPITECH PROJECT, 2020
** tree2
** File description:
** tree_traversal
*/

#include "tree_traversal.h"
#include "stack.h"
#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

void tree_traversal(tree_t tree, container_t *container, dump_func_t dump_func)
{
    list_t list;
    tree_t node;

    if (tree == NULL)
        return;
    list = tree->children;
    tree_node_dump(tree, dump_func);
    while (list != NULL) {
        node = (tree_t)list->value;
        container->push_func(container->container, node);
        list = list->next;
    }
    if (container != NULL)
        tree_traversal((tree_t)container->pop_func(container->container), \
container, dump_func);
}