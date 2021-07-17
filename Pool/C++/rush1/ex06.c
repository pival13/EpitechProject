/*
** EPITECH PROJECT, 2020
** ex06.c
** File description:
** Test main for ex6/bonus
*/

#include <stdio.h>
#include "list.h"
#include "int.h"
#include "new.h"
#include "point.h"

int main(void)
{
    // New test
    Object *list = new(List, Int);
    Object *list2 = new(List, Point);
    char *s;

    // Additem tests    :   6 40 3 2 5 1 4 987465 
    //                      

    pushfront(list, 1);
    pushfront(list, 2);
    pushfront(list, 3);
    pushback(list, 987465);
    additem(list, 3, 4);
    additem(list, 2, 5);
    additem(list, 0, 6);
    additem(list, 1, 40);

    additem(list2, 0, 0, 1);
    additem(list2, 0, 2, 5);
    additem(list2, 0, 3, 4);
    additem(list2, 3, 4, 15);
    additem(list2, 2, 5, 12);
    additem(list2, 0, 6, 985);
    additem(list2, 1, 40, 9999999);

    // Delitem tests    :   40 1 2 5 3 4
    delitem(list, 0);

    // Pushfront test   :   8 40 1 2 5 3 4
    pushfront(list, 8);

    // Popback test     :   8 40 1 2 5 3
    popback(list);

    // Begin/End test   :   begin : 8, end : NULL
    Object  *it = begin(list);
    Object  *it_end = end(list);

    // Setitem test     :   8 40 1 2 12 3
    setitem(list, 4, 12);

    // Len test         :   7
    printf("list size: %zu\n", len(list));

    // Iterator + getval test   :   <Int 8>\n<Int 40>...
    printf("Iterator tests :\n");
    while (lt(it, it_end))
    {
        s = str(getval(it));
        printf("%s\n", s);
        free(s);
        incr(it);
    }

    // List display test
    printf("\nList display test :\n");
    s = str(list);
    printf("%s\n\n", s);
    free(s);

    
    setitem(list, 1, -1458);
    s = str(getitem(list, 1));
    printf("List[%d] = %s\n\n", 1, s);
    free(s);
    s = str(front(list));
    printf("Front : %s\n", s);
    free(s);
    s = str(back(list));
    printf("Back : %s\n\n", s);
    free(s);

    s = str(list2);
    printf("Before pop :\n%s\n\n", s);
    free(s);

    popfront(list2);
    popback(list2);

    s = str(list2);
    printf("After pop :\n%s\n", s);
    free(s);

    // Delete tests Iterator and Listclass
    delete(it);
    delete(it_end);
    delete(list);
    delete(list2);
    return (0);
}

