/*
** EPITECH PROJECT, 2020
** cpp_d09_2019 [WSL: Ubuntu]
** File description:
** test
*/

#include <gtest/gtest.h>
#include "Character.hpp"

TEST(Character, default_behaviour)
{
    Character c("Toto", 1);
    c.TakeDamage(c.CloseAttack());

    EXPECT_EQ(c.getPv(), 85);
}
