/*
** EPITECH PROJECT, 2020
** koalatchi.c
** File description:
** Something related to koala
*/

#include <stdint.h>
#include <stdio.h>

char *nutrition(uint32_t header)
{
    if (header == 0x01010001)
        return "Notification Nutrition Eat";
    if (header == 0x01010002)
        return "Notification Nutrition Defecate";
    if (header == 0x02010001)
        return "Request Nutrition Hungry";
    if (header == 0x02010002)
        return "Request Nutrition Thirsty";
    if (header == 0x04010001)
        return "Error Nutrition Indigestion";
    if (header == 0x04010002)
        return "Error Nutrition Starvation";
    return NULL;
}

char *entertainment(uint32_t header)
{
    if (header == 0x01020001)
        return "Notification Entertainment Ball";
    if (header == 0x01020002)
        return "Notification Entertainment Bite";
    if (header == 0x02020001)
        return "Request Entertainment NeedAffection";
    if (header == 0x02020002)
        return "Request Entertainment WannaPlay";
    if (header == 0x02020003)
        return "Request Entertainment Hug";
    if (header == 0x04020001)
        return "Error Entertainment Bored";
    return NULL;
}

char *education(uint32_t header)
{
    if (header == 0x01040001)
        return "Notification Education TeachCoding";
    if (header == 0x01040002)
        return "Notification Education BeAwesome";
    if (header == 0x02040001)
        return "Request Education FeelStupid";
    if (header == 0x04040001)
        return "Error Education BrainDamage";
    return NULL;
}

int prettyprint_message(uint32_t header, const char *content)
{
    uint8_t domain = (header >> 16) & 0xFF;
    char *action = NULL;

    if (domain == 1)
        action = nutrition(header);
    if (domain == 2)
        action = entertainment(header);
    if (domain == 4)
        action = education(header);
    if (action == NULL) {
        printf("Invalid message.\n");
        return 1;
    }
    if (content)
        printf("%s %s\n", action, content);
    else
        printf("%s\n", action);
    return 0;
}